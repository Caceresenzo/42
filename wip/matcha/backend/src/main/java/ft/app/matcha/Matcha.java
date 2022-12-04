package ft.app.matcha;

import java.util.Arrays;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.mysql.cj.jdbc.MysqlConnectionPoolDataSource;

import ft.app.matcha.domain.like.Like;
import ft.app.matcha.domain.notification.Notification;
import ft.app.matcha.domain.picture.PictureController;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserController;
import ft.app.matcha.security.JwtAuthenticationFilter;
import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.http.convert.SimpleHttpMessageConversionService;
import ft.framework.mvc.http.convert.impl.InputStreamHttpMessageConverter;
import ft.framework.mvc.http.convert.impl.JacksonHttpMessageConverter;
import ft.framework.mvc.mapping.RouteRegistry;
import ft.framework.mvc.resolver.argument.impl.BodyHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.PageableHandlerMethodArgumentResolver;
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
import io.swagger.models.Info;
import io.swagger.models.Swagger;
import lombok.SneakyThrows;

public class Matcha {
	
	@SneakyThrows
	public static void main(String[] args) {
		final var ormConfiguration = configureOrm();
		final var mvcConfiguration = configureMvc();
		
		final var routeRegistry = new RouteRegistry(mvcConfiguration);
		
		routeRegistry.add(new PictureController());
		routeRegistry.add(new UserController(ormConfiguration.getEntityManager()));
		
		final var swagger = new Swagger()
			.info(new Info()
				.title("Matcha")
				.version("1.0"));
		
		SwaggerBuilder.build(swagger, routeRegistry.getRoutes());
		routeRegistry.add(new SwaggerController(swagger));
		
		routeRegistry.markReady();
	}
	
	@SneakyThrows
	public static OrmConfiguration configureOrm() {
		final var dataSource = new MysqlConnectionPoolDataSource();
		dataSource.setServerName("localhost");
		dataSource.setUser("root");
		dataSource.setPassword("password");
		dataSource.setDatabaseName("matcha");
		dataSource.setAutoReconnect(true);
		dataSource.setAutoReconnectForPools(true);
		
		final var dialect = new MySQLDialect();
		
		final var mappingBuilder = new MappingBuilder();
		Arrays.asList(User.class, Notification.class, Like.class)
			.stream()
			.forEach(mappingBuilder::analyze);
		
		return OrmConfiguration.builder()
			.entityManager(new EntityManager(dataSource, dialect, mappingBuilder))
			.build();
	}
	
	@SneakyThrows
	public static MvcConfiguration configureMvc() {
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
				new BodyHandlerMethodArgumentResolver(objectMapper)))
			.filter(new JwtAuthenticationFilter())
			.filter(new LoggingFilter())
			.build();
	}
	
}