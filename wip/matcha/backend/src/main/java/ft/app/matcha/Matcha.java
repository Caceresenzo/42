package ft.app.matcha;

import java.util.Arrays;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.mysql.cj.jdbc.MysqlConnectionPoolDataSource;

import ft.app.matcha.domain.auth.AuthController;
import ft.app.matcha.domain.auth.AuthService;
import ft.app.matcha.domain.auth.JwtService;
import ft.app.matcha.domain.auth.RefreshToken;
import ft.app.matcha.domain.auth.RefreshTokenRepository;
import ft.app.matcha.domain.auth.RefreshTokenService;
import ft.app.matcha.domain.like.Like;
import ft.app.matcha.domain.notification.Notification;
import ft.app.matcha.domain.picture.PictureController;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserController;
import ft.app.matcha.domain.user.UserRepository;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.security.JwtAuthenticationFilter;
import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.http.convert.SimpleHttpMessageConversionService;
import ft.framework.mvc.http.convert.impl.InputStreamHttpMessageConverter;
import ft.framework.mvc.http.convert.impl.JacksonHttpMessageConverter;
import ft.framework.mvc.mapping.RouteRegistry;
import ft.framework.mvc.resolver.argument.impl.AuthenticationHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.BodyHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.PageableHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.PrincipalHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.QueryHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.RequestHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.ResponseHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.VariableHandlerMethodArgumentResolver;
import ft.framework.orm.EntityManager;
import ft.framework.orm.OrmConfiguration;
import ft.framework.orm.dialect.MySQLDialect;
import ft.framework.orm.mapping.MappingBuilder;
import ft.framework.swagger.SwaggerBuilder;
import ft.framework.swagger.controller.SwaggerController;
import ft.framework.trace.filter.LoggingFilter;
import io.jsonwebtoken.security.Keys;
import io.swagger.models.Info;
import io.swagger.models.Swagger;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class Matcha {
	
	@SneakyThrows
	public static void main(String[] args) {
		final var key = Keys.hmacShaKeyFor("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx".getBytes());
		
		final var ormConfiguration = configureOrm(User.class, RefreshToken.class, Notification.class, Like.class);
		
		final var userRepository = new UserRepository(ormConfiguration.getEntityManager());
		final var refreshTokenRepository = new RefreshTokenRepository(ormConfiguration.getEntityManager());
		
		final var userService = new UserService(userRepository);
		final var jwtService = new JwtService(key, userRepository);
		final var refreshTokenService = new RefreshTokenService(refreshTokenRepository);
		final var authService = new AuthService(userService, refreshTokenService, jwtService);
		
		final var mvcConfiguration = configureMvc(jwtService);
		final var routeRegistry = new RouteRegistry(mvcConfiguration);
		
		routeRegistry.add(new AuthController(authService));
		routeRegistry.add(new PictureController());
		routeRegistry.add(new UserController(userRepository));
		
		final var swagger = new Swagger()
			.info(new Info()
				.title("Matcha")
				.version("1.0"));
		
		SwaggerBuilder.build(swagger, routeRegistry.getRoutes());
		routeRegistry.add(new SwaggerController(swagger));
		
		routeRegistry.markReady();
	}
	
	@SneakyThrows
	public static OrmConfiguration configureOrm(Class<?>... entityClasses) {
		final var dataSource = new MysqlConnectionPoolDataSource();
		dataSource.setServerName("localhost");
		dataSource.setUser("root");
		dataSource.setPassword("password");
		dataSource.setDatabaseName("matcha");
		dataSource.setAutoReconnect(true);
		dataSource.setAutoReconnectForPools(true);
		
		final var dialect = new MySQLDialect();
		
		final var mappingBuilder = new MappingBuilder();
		Arrays.stream(entityClasses)
			.forEach(mappingBuilder::analyze);
		
		final var configuration = OrmConfiguration.builder()
			.entityManager(new EntityManager(dataSource, dialect, mappingBuilder))
			.build();
		
		for (final var entity : mappingBuilder.getEntities()) {
			System.out.println(dialect.buildCreateTableStatement(entity.getTable()));
		}
		
		for (final var entity : mappingBuilder.getEntities()) {
			final var table = entity.getTable();
			
			for (final var manyToOne : table.getManyToOnes()) {
				System.out.println(dialect.buildAlterTableAddForeignKeyStatement(table, manyToOne));
			}
			
			for (final var index : table.getIndexes()) {
				System.out.println(dialect.buildCreateIndexStatement(table, index));
			}
			
			for (final var unique : table.getUniques()) {
				System.out.println(dialect.buildAlterTableAddUniqueStatement(table, unique));
			}
		}
		
		return configuration;
	}
	
	@SneakyThrows
	public static MvcConfiguration configureMvc(JwtService jwtService) {
		log.info("Waking up");
		
		final var objectMapper = new ObjectMapper()
			.disable(SerializationFeature.FAIL_ON_EMPTY_BEANS);
		
		return MvcConfiguration.builder()
			.objectMapper(objectMapper)
			.httpMessageConversionService(
				SimpleHttpMessageConversionService.builder()
					.converter(new InputStreamHttpMessageConverter())
					.converter(new JacksonHttpMessageConverter(objectMapper, true))
					.build())
			.methodArgumentResolvers(Arrays.asList(
				new VariableHandlerMethodArgumentResolver(),
				new QueryHandlerMethodArgumentResolver(),
				new RequestHandlerMethodArgumentResolver(),
				new ResponseHandlerMethodArgumentResolver(),
				new PageableHandlerMethodArgumentResolver(),
				new AuthenticationHandlerMethodArgumentResolver(),
				new PrincipalHandlerMethodArgumentResolver(),
				new BodyHandlerMethodArgumentResolver(objectMapper)))
			.filter(new JwtAuthenticationFilter(jwtService))
			.filter(new LoggingFilter())
			.build();
	}
	
}