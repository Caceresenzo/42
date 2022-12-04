package ft.app.matcha;

import java.util.Arrays;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.mysql.cj.jdbc.MysqlConnectionPoolDataSource;

import ft.app.matcha.controller.PictureController;
import ft.app.matcha.controller.UserController;
import ft.app.matcha.entity.Like;
import ft.app.matcha.entity.Notification;
import ft.app.matcha.entity.User;
import ft.app.matcha.security.JwtAuthenticationFilter;
import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.http.convert.SimpleHttpMessageConversionService;
import ft.framework.mvc.http.convert.impl.InputStreamHttpMessageConverter;
import ft.framework.mvc.http.convert.impl.JacksonHttpMessageConverter;
import ft.framework.mvc.mapping.RouteRegistry;
import ft.framework.mvc.resolver.argument.impl.BodyHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.ParameterHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.QueryHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.RequestHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.ResponseHandlerMethodArgumentResolver;
import ft.framework.orm.EntityManager;
import ft.framework.orm.dialect.MySQLDialect;
import ft.framework.orm.mapping.MappingBuilder;
import ft.framework.trace.filter.LoggingFilter;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class Matcha {
	
	@SneakyThrows
	public static void main(String[] args) {
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
		
		final var entityManager = new EntityManager(dataSource, dialect, mappingBuilder);
		final var entities = entityManager.getEntities();
		
//		System.out.println(new ObjectMapper().writerWithDefaultPrettyPrinter().writeValueAsString(entities));
//		
//		for (final var entity : entities) {
//			System.out.println(dialect.buildCreateTableStatement(entity.getTable()));
//		}
//		
//		for (final var entity : entities) {
//			final var table = entity.getTable();
//			
//			for (final var manyToOne : table.getManyToOnes()) {
//				System.out.println(dialect.buildAlterTableAddForeignKeyStatement(table, manyToOne));
//			}
//		}
//		
//		final var user = new User().setName("Enzo");
//		entityManager.persist(user);
//		
//		System.out.println(user);
//		
//		final var notification = new Notification().setContent("Welcome").setUser(user).setCreatedAt(LocalDateTime.now());
//		entityManager.persist(notification);
//		
//		notification.setContent("Nice");
//		entityManager.persist(notification);
//		
//		System.out.println(notification);
		
		final var enzo = entityManager.find(User.class, 1).get();
		System.out.println(enzo);
		enzo.setName("dorian");
		System.out.println(enzo);
		
		System.out.println(entityManager.update(enzo));
		System.out.println(entityManager.update(enzo));
		
		System.out.println();

		final var jules = entityManager.persist(new User().setName("jules"));
		System.out.println(entityManager.update(jules));
		System.out.println(jules);
		jules.setName("juju");
		System.out.println(entityManager.update(jules));
		
//		final var notifications = entityManager.findAll(Notification.class);
//		notifications.forEach(System.out::println);
	}
	
	@SneakyThrows
	public static void main2(String[] args) {
		final var objectMapper = new ObjectMapper()
			.disable(SerializationFeature.FAIL_ON_EMPTY_BEANS);
		
		final var mvcConfiguration = MvcConfiguration.builder()
			.objectMapper(objectMapper)
			.httpMessageConversionService(
				SimpleHttpMessageConversionService.builder()
					.converter(new InputStreamHttpMessageConverter())
					.converter(new JacksonHttpMessageConverter(objectMapper, true))
					.build())
			.methodArgumentResolvers(Arrays.asList(
				new ParameterHandlerMethodArgumentResolver(),
				new QueryHandlerMethodArgumentResolver(),
				new RequestHandlerMethodArgumentResolver(),
				new ResponseHandlerMethodArgumentResolver(),
				new BodyHandlerMethodArgumentResolver(objectMapper)))
			.filter(new JwtAuthenticationFilter())
			.filter(new LoggingFilter())
			.build();
		
		final var routeRegistry = new RouteRegistry(mvcConfiguration);
		
		routeRegistry.add(new PictureController());
		routeRegistry.add(new UserController());
		
		routeRegistry.markReady();
	}
	
}