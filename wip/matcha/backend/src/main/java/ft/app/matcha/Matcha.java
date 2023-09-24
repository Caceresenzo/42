package ft.app.matcha;

import java.util.Arrays;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.databind.module.SimpleModule;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import com.mysql.cj.jdbc.MysqlConnectionPoolDataSource;

import ft.app.matcha.configuration.AuthConfigurationProperties;
import ft.app.matcha.configuration.DatabaseConfigurationProperties;
import ft.app.matcha.configuration.EmailConfigurationProperties;
import ft.app.matcha.configuration.HeartbeatConfigurationProperties;
import ft.app.matcha.configuration.MatchaConfigurationProperties;
import ft.app.matcha.configuration.SwaggerConfigurationProperties;
import ft.app.matcha.configuration.UrlConfigurationProperties;
import ft.app.matcha.domain.auth.AuthService;
import ft.app.matcha.domain.auth.EmailSender;
import ft.app.matcha.domain.auth.JwtService;
import ft.app.matcha.domain.auth.OAuthService;
import ft.app.matcha.domain.auth.Token;
import ft.app.matcha.domain.auth.TokenRepository;
import ft.app.matcha.domain.auth.TokenService;
import ft.app.matcha.domain.heartbeat.Heartbeat;
import ft.app.matcha.domain.heartbeat.HeartbeatRepository;
import ft.app.matcha.domain.heartbeat.HeartbeatService;
import ft.app.matcha.domain.heartbeat.IpLocationResolverService;
import ft.app.matcha.domain.location.Location;
import ft.app.matcha.domain.location.LocationRepository;
import ft.app.matcha.domain.location.LocationService;
import ft.app.matcha.domain.message.Message;
import ft.app.matcha.domain.message.MessageRepository;
import ft.app.matcha.domain.message.MessageService;
import ft.app.matcha.domain.notification.Notification;
import ft.app.matcha.domain.notification.NotificationRepository;
import ft.app.matcha.domain.notification.NotificationService;
import ft.app.matcha.domain.picture.DefaultPicture;
import ft.app.matcha.domain.picture.DefaultPictureRepository;
import ft.app.matcha.domain.picture.Picture;
import ft.app.matcha.domain.picture.PictureRepository;
import ft.app.matcha.domain.picture.PictureService;
import ft.app.matcha.domain.relationship.Relationship;
import ft.app.matcha.domain.relationship.RelationshipRepository;
import ft.app.matcha.domain.relationship.RelationshipService;
import ft.app.matcha.domain.report.Report;
import ft.app.matcha.domain.report.ReportRepository;
import ft.app.matcha.domain.report.ReportService;
import ft.app.matcha.domain.tag.Tag;
import ft.app.matcha.domain.tag.TagRepository;
import ft.app.matcha.domain.tag.TagService;
import ft.app.matcha.domain.tag.UserTag;
import ft.app.matcha.domain.tag.UserTagRepository;
import ft.app.matcha.domain.tag.UserTagService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserRepository;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.visit.Visit;
import ft.app.matcha.domain.visit.VisitRepository;
import ft.app.matcha.domain.visit.VisitService;
import ft.app.matcha.security.jwt.JwtAuthenticator;
import ft.app.matcha.security.jwt.JwtCookieAuthenticationFilter;
import ft.app.matcha.security.jwt.JwtHeaderAuthenticationFilter;
import ft.app.matcha.web.AuthController;
import ft.app.matcha.web.BlockController;
import ft.app.matcha.web.HeartbeatController;
import ft.app.matcha.web.LikeController;
import ft.app.matcha.web.LocationController;
import ft.app.matcha.web.MessageController;
import ft.app.matcha.web.NotificationController;
import ft.app.matcha.web.PictureController;
import ft.app.matcha.web.ReportController;
import ft.app.matcha.web.TagController;
import ft.app.matcha.web.UserController;
import ft.app.matcha.web.UserTagController;
import ft.app.matcha.web.VisitController;
import ft.app.matcha.web.WebSocketController;
import ft.app.matcha.web.map.LocationMapper;
import ft.app.matcha.web.map.PictureMapper;
import ft.app.matcha.web.map.RelationshipMapper;
import ft.app.matcha.web.map.ReportMapper;
import ft.app.matcha.web.map.TagMapper;
import ft.app.matcha.web.map.UserMapper;
import ft.app.matcha.web.map.VisitMapper;
import ft.framework.convert.service.ConvertionService;
import ft.framework.convert.service.SimpleConvertionService;
import ft.framework.event.ApplicationEventPublisher;
import ft.framework.event.listener.EventListenerFactory;
import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.http.convert.SimpleHttpMessageConversionService;
import ft.framework.mvc.http.convert.impl.InputStreamHttpMessageConverter;
import ft.framework.mvc.http.convert.impl.JacksonHttpMessageConverter;
import ft.framework.mvc.mapping.RouteRegistry;
import ft.framework.mvc.resolver.argument.impl.AuthenticationHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.BodyHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.FormDataHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.InetAddressHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.PageableHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.PrincipalHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.QueryHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.RequestHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.ResponseHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.VariableHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.exception.DefaultHandlerExceptionResolver;
import ft.framework.mvc.security.CompositeAuthenticationFilter;
import ft.framework.orm.EntityManager;
import ft.framework.orm.OrmConfiguration;
import ft.framework.orm.dialect.MySQLDialect;
import ft.framework.orm.mapping.MappingBuilder;
import ft.framework.property.PropertyBinder;
import ft.framework.property.resolver.EnvironmentPropertyResolver;
import ft.framework.schedule.ScheduledFactory;
import ft.framework.schedule.impl.WispTaskScheduler;
import ft.framework.swagger.SwaggerBuilder;
import ft.framework.swagger.controller.SwaggerController;
import ft.framework.trace.filter.LoggingFilter;
import ft.framework.util.StringTrimDeserializer;
import ft.framework.validation.ValidationException;
import ft.framework.validation.Validator;
import ft.framework.websocket.WebSocketHandler;
import io.github.cdimascio.dotenv.Dotenv;
import io.swagger.v3.oas.models.OpenAPI;
import io.swagger.v3.oas.models.info.Info;
import io.swagger.v3.oas.models.security.SecurityScheme;
import io.swagger.v3.oas.models.servers.Server;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import okhttp3.OkHttpClient;

@Slf4j
public class Matcha {
	
	@SuppressWarnings("serial")
	public static class MatchaJacksonModule extends SimpleModule {
		
		public MatchaJacksonModule() {
			addDeserializer(String.class, new StringTrimDeserializer());
		}
		
	}
	
	@SneakyThrows
	public static void main(String[] args) {
		try {
			Dotenv.configure()
				.systemProperties()
				.ignoreIfMissing()
				.load();
			
			final var objectMapper = new ObjectMapper()
				.disable(SerializationFeature.FAIL_ON_EMPTY_BEANS)
				.registerModule(new JavaTimeModule())
				.registerModule(new MatchaJacksonModule());
			
			final var httpClient = new OkHttpClient.Builder()
				.build();
			
			final var validator = new Validator();
			final var convertionService = new SimpleConvertionService();
			
			final var propertyBinder = PropertyBinder.builder()
				.validator(validator)
				.convertionService(convertionService)
				.resolver(new EnvironmentPropertyResolver())
				.build();
			
			final var databaseConfiguration = propertyBinder.bind(new DatabaseConfigurationProperties());
			final var authConfiguration = propertyBinder.bind(new AuthConfigurationProperties());
			final var emailConfiguration = propertyBinder.bind(new EmailConfigurationProperties());
			final var matchaConfiguration = propertyBinder.bind(new MatchaConfigurationProperties());
			final var heartbeatConfiguration = propertyBinder.bind(new HeartbeatConfigurationProperties());
			final var swaggerConfiguration = propertyBinder.bind(new SwaggerConfigurationProperties());
			final var urlConfiguration = propertyBinder.bind(new UrlConfigurationProperties());
			
			final var ormConfiguration = configureOrm(databaseConfiguration, new Class<?>[] {
				User.class,
				Notification.class,
				Relationship.class,
				Token.class,
				Picture.class,
				DefaultPicture.class,
				Tag.class,
				UserTag.class,
				Message.class,
				Report.class,
				Relationship.class,
				Visit.class,
				Heartbeat.class,
				Location.class,
			});
			
			final var webSocket = WebSocketHandler.create(objectMapper);
			
			final var eventPublisher = new ApplicationEventPublisher();
			final var taskScheduler = new WispTaskScheduler();
			
			final var userRepository = new UserRepository(ormConfiguration.getEntityManager());
			final var notificationRepository = new NotificationRepository(ormConfiguration.getEntityManager());
			final var tokenRepository = new TokenRepository(ormConfiguration.getEntityManager());
			final var pictureRepository = new PictureRepository(ormConfiguration.getEntityManager());
			final var defaultPictureRepository = new DefaultPictureRepository(ormConfiguration.getEntityManager());
			final var tagRepository = new TagRepository(ormConfiguration.getEntityManager());
			final var userTagRepository = new UserTagRepository(ormConfiguration.getEntityManager());
			final var messageRepository = new MessageRepository(ormConfiguration.getEntityManager());
			final var reportRepository = new ReportRepository(ormConfiguration.getEntityManager());
			final var relationshipRepository = new RelationshipRepository(ormConfiguration.getEntityManager());
			final var visitRepository = new VisitRepository(ormConfiguration.getEntityManager());
			final var heartbeatRepository = new HeartbeatRepository(ormConfiguration.getEntityManager());
			final var locationRepository = new LocationRepository(ormConfiguration.getEntityManager());
			
			final var emailSender = new EmailSender(emailConfiguration, urlConfiguration);
			
			final var userService = new UserService(userRepository, matchaConfiguration);
			final var jwtService = new JwtService(userRepository, authConfiguration);
			final var tokenService = new TokenService(tokenRepository, authConfiguration, eventPublisher);
			final var pictureService = new PictureService(pictureRepository, defaultPictureRepository, httpClient, matchaConfiguration);
			final var oAuthService = new OAuthService(objectMapper, httpClient, authConfiguration);
			final var authService = new AuthService(tokenService, userService, jwtService, emailSender, oAuthService, pictureService, eventPublisher);
			final var relationshipService = new RelationshipService(relationshipRepository, eventPublisher);
			final var tagService = new TagService(tagRepository);
			final var userTagService = new UserTagService(userTagRepository, matchaConfiguration);
			final var messageService = new MessageService(messageRepository, eventPublisher, relationshipService);
			final var jwtAuthenticator = new JwtAuthenticator(jwtService);
			final var webSocketService = new WebSocketController(webSocket, jwtAuthenticator);
			final var reportService = new ReportService(reportRepository, eventPublisher);
			final var notificationService = new NotificationService(notificationRepository, relationshipService, eventPublisher);
			final var visitService = new VisitService(visitRepository, eventPublisher);
			final var ipLocationService = new IpLocationResolverService(httpClient, heartbeatConfiguration);
			final var heartbeatService = new HeartbeatService(heartbeatRepository, ipLocationService, eventPublisher, heartbeatConfiguration);
			final var locationService = new LocationService(locationRepository);
			
			final var services = Arrays.asList(new Object[] {
				userService,
				jwtService,
				authService,
				notificationService,
				pictureService,
				tagService,
				userTagService,
				messageService,
				webSocketService,
				reportService,
				relationshipService,
				visitService,
				ipLocationService,
				heartbeatService,
				locationService,
			});
			
			final var eventListenerFactory = new EventListenerFactory(eventPublisher);
			services.forEach(eventListenerFactory::scan);
			
			final var scheduledFactory = new ScheduledFactory(taskScheduler);
			services.forEach(scheduledFactory::scan);
			
			final var locationMapper = new LocationMapper();
			final var pictureMapper = new PictureMapper(pictureService);
			final var relationshipMapper = new RelationshipMapper(relationshipService);
			final var userMapper = new UserMapper(relationshipMapper, pictureService, pictureMapper, heartbeatService, locationService, locationMapper);
			final var reportMapper = new ReportMapper(userMapper);
			final var visitMapper = new VisitMapper(userMapper);
			final var tagMapper = new TagMapper(userTagService);
			
			final var mvcConfiguration = configureMvc(objectMapper, validator, convertionService, jwtAuthenticator, authService);
			final var routeRegistry = new RouteRegistry(mvcConfiguration);
			
			routeRegistry.add(new AuthController(authService, userMapper));
			routeRegistry.add(new PictureController(userService, pictureService, pictureMapper));
			routeRegistry.add(new UserController(userService, userMapper));
			routeRegistry.add(new LikeController(relationshipService, userService, userMapper));
			routeRegistry.add(new TagController(tagService, userTagService, tagMapper, userMapper));
			routeRegistry.add(new UserTagController(userTagService, userService, tagService, tagMapper));
			routeRegistry.add(new MessageController(messageService, userService));
			routeRegistry.add(new NotificationController(notificationService));
			routeRegistry.add(new ReportController(reportService, userService, reportMapper));
			routeRegistry.add(new BlockController(relationshipService, userService, userMapper));
			routeRegistry.add(new VisitController(visitService, userService, visitMapper));
			routeRegistry.add(new HeartbeatController(heartbeatService));
			routeRegistry.add(new LocationController(locationService, userService, locationMapper));
			
			final var swagger = new OpenAPI()
				.schemaRequirement("JWT", new SecurityScheme()
					.type(SecurityScheme.Type.HTTP)
					.scheme("bearer")
					.bearerFormat("JWT"))
				.info(new Info()
					.title("Matcha")
					.version("1.0"));
			
			swagger.addServersItem(
				new Server()
					.description(swaggerConfiguration.getServerName())
					.url(swaggerConfiguration.getServerUrl())
			);
			
			SwaggerBuilder.build(swagger, routeRegistry.getRoutes());
			routeRegistry.add(new SwaggerController(swagger));
			
			routeRegistry.markReady();
		} catch (ValidationException exception) {
			log.error("A model could not be validated", exception);
			
			final var violations = exception.getViolations();
			for (final var violation : violations) {
				log.error("{}: {}", violation.getPropertyPath(), violation.getMessage());
			}
			
			System.exit(1);
		} catch (Exception exception) {
			log.error("Could start the server", exception);
			System.exit(1);
		}
	}
	
	@SneakyThrows
	public static OrmConfiguration configureOrm(DatabaseConfigurationProperties databaseConfiguration, Class<?>... entityClasses) {
		final var dataSource = new MysqlConnectionPoolDataSource();
		dataSource.setServerName(databaseConfiguration.getHost());
		dataSource.setPort(databaseConfiguration.getPort());
		dataSource.setUser(databaseConfiguration.getUser());
		dataSource.setPassword(databaseConfiguration.getPassword());
		dataSource.setDatabaseName(databaseConfiguration.getDatabase());
		dataSource.setAutoReconnect(databaseConfiguration.isAutoReconnect());
		dataSource.setAutoReconnectForPools(databaseConfiguration.isAutoReconnect());
		
		final var dialect = new MySQLDialect();
		
		final var mappingBuilder = new MappingBuilder();
		Arrays.stream(entityClasses)
			.forEach(mappingBuilder::analyze);
		
		final var entityManager = new EntityManager(dataSource, dialect, mappingBuilder);
		entityManager.applyDataDefinitionLanguage();
		
		return OrmConfiguration.builder()
			.entityManager(entityManager)
			.build();
	}
	
	@SneakyThrows
	public static MvcConfiguration configureMvc(ObjectMapper objectMapper, Validator validator, ConvertionService conversionService, JwtAuthenticator jwtAuthenticator, AuthService authService) {
		log.info("Waking up");
		
		return MvcConfiguration.builder()
			.objectMapper(objectMapper)
			.validator(validator)
			.conversionService(conversionService)
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
				new PageableHandlerMethodArgumentResolver(validator),
				new AuthenticationHandlerMethodArgumentResolver(),
				new PrincipalHandlerMethodArgumentResolver(),
				new FormDataHandlerMethodArgumentResolver(),
				new InetAddressHandlerMethodArgumentResolver(),
				new BodyHandlerMethodArgumentResolver(objectMapper)))
			.filter(CompositeAuthenticationFilter.builder()
				.filter(new JwtHeaderAuthenticationFilter(jwtAuthenticator))
				.filter(new JwtCookieAuthenticationFilter(jwtAuthenticator, authService))
				.build())
			.filter(new LoggingFilter())
			.exceptionResolver(new DefaultHandlerExceptionResolver())
			.build();
	}
	
}