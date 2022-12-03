package ft.framework.mvc.mapping;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.function.Consumer;

import org.apache.commons.lang3.reflect.MethodUtils;
import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.ResponseStatus;
import ft.framework.mvc.annotation.RestController;
import ft.framework.mvc.exception.RouteNotFoundException;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import ft.framework.util.MediaTypes;
import lombok.Data;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import spark.ExceptionHandler;
import spark.Request;
import spark.Response;
import spark.Spark;

@Data
@Slf4j
public class RouteRegistry {
	
	private final MvcConfiguration configuration;
	
	@SneakyThrows
	public List<Route> extractRoutes(Object container) {
		final var routes = new ArrayList<Route>();
		
		var root = "/";
		var consume = MediaTypes.JSON;
		var produce = MediaTypes.JSON;
		
		final var rootMappingAnnotation = container.getClass().getAnnotation(RestController.class);
		if (rootMappingAnnotation != null) {
			root = rootMappingAnnotation.path();
			consume = rootMappingAnnotation.consume();
			produce = rootMappingAnnotation.produce();
		}
		
		for (final var method : container.getClass().getMethods()) {
			for (final var annotation : method.getAnnotations()) {
				final var mappingAnnotation = annotation.annotationType().getAnnotation(RestController.class);
				if (mappingAnnotation == null) {
					continue;
				}
				
				final var httpMethod = mappingAnnotation.method();
				final var path = (String) MethodUtils.invokeExactMethod(annotation, "path");
				
				final var fullPath = String.format("%s/%s", root, path)
					.replaceAll("\\/\\/+", "/")
					.replaceFirst("\\/$", "");
				
				final var route = Route.builder()
					.path(fullPath)
					.httpMethod(httpMethod)
					.container(container)
					.method(method)
					.consume(consume)
					.produce(produce)
					.build();
				
				routes.add(route);
			}
		}
		
		return routes;
	}
	
	public <T> T add(T container) {
		final var routes = extractRoutes(container);
		
		for (final var route : routes) {
			final var handler = createHandler(route);
			
			registerToSpark(route, handler);
			
			log.info("Registered: {} {} -> {} [{} -> {}]", route.getHttpMethod(), route.getPath(), route.getMethod(), route.getConsume(), route.getProduce());
		}
		
		return container;
	}
	
	public RouteHandler createHandler(Route route) {
		final var argumentResolvers = getArgumentResolvers(route);
		final var responseCustomizers = getResponseCustomizers(route);
		
		return new RouteHandler(route, argumentResolvers, responseCustomizers, configuration);
	}
	
	@SneakyThrows
	public HandlerMethodArgumentResolver[] getArgumentResolvers(Route route) {
		final var parameters = route.getMethod().getParameters();
		
		final var argumentResolvers = new HandlerMethodArgumentResolver[parameters.length];
		
		for (var index = 0; index < parameters.length; ++index) {
			final var parameter = parameters[index];
			
			argumentResolvers[index] = configuration.getMethodArgumentResolvers()
				.stream()
				.filter((resolver) -> resolver.supportsParameter(parameter))
				.findFirst()
				.orElseThrow(() -> new Exception("no method argument resolver available for: " + parameter));
		}
		
		return argumentResolvers;
	}
	
	public List<Consumer<Response>> getResponseCustomizers(Route route) {
		final var customizers = new ArrayList<Consumer<Response>>();
		
		extractResponseStatus(route.getMethod()).ifPresent(customizers::add);
		
		return customizers;
	}
	
	public void markReady() {
		Spark.exception(Exception.class, new ExceptionHandler<Exception>() {
			
			@SneakyThrows
			@Override
			public void handle(Exception exception, Request request, Response response) {
				final var problem = configuration.getExceptionResolver()
					.resolveException(request.raw(), response.raw(), exception);
				
				final var status = problem.getStatus();
				if (status != null) {
					response.status(status);
				} else {
					response.status(HttpStatus.INTERNAL_SERVER_ERROR_500);
				}
				
				response.type(MediaTypes.JSON);
				response.body(configuration.getObjectMapper().writeValueAsString(problem));
				
				if (response.status() == HttpStatus.INTERNAL_SERVER_ERROR_500) {
					log.error("Could not process request", exception);
				}
			}
		});
		
		add(new FallbackController());
	}
	
	public static void registerToSpark(Route route, RouteHandler handler) {
		final var method = route.getHttpMethod();
		final var path = route.getPath();
		
		switch (method) {
			case get: {
				Spark.get(path, handler);
				break;
			}
			
			case post: {
				Spark.post(path, handler);
				break;
			}
			
			case put: {
				Spark.put(path, handler);
				break;
			}
			
			case patch: {
				Spark.patch(path, handler);
				break;
			}
			
			case delete: {
				Spark.delete(path, handler);
				break;
			}
			
			default: {
				throw new IllegalStateException(String.format("no method for %s", method));
			}
		}
	}
	
	public static Optional<Consumer<Response>> extractResponseStatus(Method method) {
		final var annotation = method.getAnnotation(ResponseStatus.class);
		
		if (annotation == null) {
			return Optional.empty();
		}
		
		final var status = annotation.value();
		return Optional.of((response) -> response.status(status));
	}
	
	public static String extractRoot(Object container) {
		final var restMapping = container.getClass().getAnnotation(RestController.class);
		if (restMapping == null) {
			return "/";
		}
		
		return restMapping.path();
	}
	
	@RestController(path = "*")
	public static class FallbackController {
		
		@GetMapping
		public void index(Request request) {
			throw new RouteNotFoundException(request.pathInfo());
		}
		
	}
	
}