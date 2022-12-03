package ft.app.matcha;

import java.util.Arrays;

import com.fasterxml.jackson.databind.ObjectMapper;

import ft.app.matcha.controller.UserController;
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
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class Matcha {
	
	// @SneakyThrows
	// public static void main(String[] args) {
	// final var dataSource = new MysqlConnectionPoolDataSource();
	// dataSource.setServerName("localhost");
	// dataSource.setUser("root");
	// dataSource.setPassword("password");
	// dataSource.setDatabaseName("matcha");
	// dataSource.setAutoReconnect(true);
	// dataSource.setAutoReconnectForPools(true);
	//
	// final var dialect = new MySQLDialect();
	//
	// // dataSource.getPooledConnection()
	//
	// final var mappingBuilder = new MappingBuilder();
	// Arrays.asList(User.class, Notification.class, Like.class)
	// .stream()
	// .forEach(mappingBuilder::analyze);
	//
	// final var entityManager = new EntityManager(dataSource, dialect, mappingBuilder);
	// final var entities = entityManager.getEntities();
	//
	// System.out.println(new ObjectMapper().writerWithDefaultPrettyPrinter().writeValueAsString(entities));
	//
	// for (final var entity : entities) {
	// System.out.println(dialect.buildCreateTableStatement(entity.getTable()));
	// }
	//
	// for (final var entity : entities) {
	// final var table = entity.getTable();
	//
	// for (final var manyToOne : table.getManyToOnes()) {
	// System.out.println(dialect.buildAlterTableAddForeignKeyStatement(table, manyToOne));
	// }
	// }
	//
	// final var user = new User().setName("Enzo");
	// entityManager.persist(user);
	//
	// System.out.println(user);
	//
	// final var notification = new Notification().setContent("Welcome").setUser(user).setCreatedAt(LocalDateTime.now());
	// entityManager.persist(notification);
	//
	// notification.setContent("Nice");
	// entityManager.persist(notification);
	//
	// System.out.println(notification);
	// }
	
	@SneakyThrows
	public static void main(String[] args) {
		final var objectMapper = new ObjectMapper();
		
		final var mvcConfiguration = MvcConfiguration.builder()
			.objectMapper(objectMapper)
			.httpMessageConversionService(
				SimpleHttpMessageConversionService.builder()
					.converter(new JacksonHttpMessageConverter(objectMapper))
					.converter(new InputStreamHttpMessageConverter())
					.build())
			.methodArgumentResolvers(Arrays.asList(
				new ParameterHandlerMethodArgumentResolver(),
				new QueryHandlerMethodArgumentResolver(),
				new RequestHandlerMethodArgumentResolver(),
				new ResponseHandlerMethodArgumentResolver(),
				new BodyHandlerMethodArgumentResolver(objectMapper)))
			.build();
		
		final var routeRegistry = new RouteRegistry(mvcConfiguration);
		
		final var userController = routeRegistry.add(new UserController());

		routeRegistry.markReady();
	}
	
}