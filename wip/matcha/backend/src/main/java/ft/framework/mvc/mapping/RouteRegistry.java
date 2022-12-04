package ft.framework.mvc.mapping;

import java.lang.annotation.Annotation;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Optional;

import org.apache.commons.lang3.reflect.MethodUtils;
import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.ResponseBody;
import ft.framework.mvc.annotation.ResponseStatus;
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
	private final List<Route> routes = new ArrayList<>();
	
	@SuppressWarnings("unchecked")
	@SneakyThrows
	public static <T> Optional<T> getValueOrParent(String methodName, Annotation annotation, Annotation parent) {
		try {
			return Optional.of((T) MethodUtils.invokeMethod(annotation, true, methodName));
		} catch (NoSuchMethodException exception) {
			if (parent != null) {
				try {
					return Optional.of((T) MethodUtils.invokeMethod(parent, true, methodName));
				} catch (NoSuchMethodException exception2) {
				}
			}
		}
		
		return Optional.empty();
	}
	
	public static String extractRoot(Object container) {
		final var restMapping = container.getClass().getAnnotation(RequestMapping.class);
		if (restMapping == null) {
			return "/";
		}
		
		return restMapping.path();
	}
	
	@SneakyThrows
	public List<Route> extractRoutes(Object container) {
		if (!container.getClass().isAnnotationPresent(Controller.class)) {
			return Collections.emptyList();
		}
		
		final var routes = new ArrayList<Route>();
		
		var root = "/";
		final var authenticated = container.getClass().isAnnotationPresent(Authenticated.class);
		
		final var parentAnnotation = container.getClass().getAnnotation(RequestMapping.class);
		if (parentAnnotation != null) {
			root = parentAnnotation.path();
		}
		
		for (final var method : container.getClass().getMethods()) {
			for (final var annotation : method.getAnnotations()) {
				final var mappingAnnotation = annotation.annotationType().getAnnotation(RequestMapping.class);
				if (mappingAnnotation == null) {
					continue;
				}
				
				final var httpMethod = mappingAnnotation.method();
				final var path = (String) MethodUtils.invokeExactMethod(annotation, "path");
				
				final var consume = RouteRegistry.<String>getValueOrParent("consume", annotation, parentAnnotation).orElse(MediaTypes.JSON);
				final var produce = RouteRegistry.<String>getValueOrParent("produce", annotation, parentAnnotation).orElse(MediaTypes.JSON);
				
				final var fullPath = String.format("%s/%s", root, path)
					.replaceAll("\\/\\/+", "/")
					.replaceFirst("(?<!^)\\/$", "");
				
				final var route = Route.builder()
					.path(fullPath)
					.httpMethod(httpMethod)
					.container(container)
					.method(method)
					.consume(consume)
					.produce(produce);
				
				if (authenticated || method.isAnnotationPresent(Authenticated.class)) {
					route.authenticated(true);
				}
				
				if (method.isAnnotationPresent(ResponseBody.class) || method.getAnnotatedReturnType().isAnnotationPresent(ResponseBody.class)) {
					route.responseBody(true);
				}
				
				final var responseStatus = method.getAnnotation(ResponseStatus.class);
				if (responseStatus != null) {
					route.responseStatus(responseStatus.value());
				}
				
				routes.add(route.build());
			}
		}
		
		return routes;
	}
	
	public <T> T add(T container) {
		final var routes = extractRoutes(container);
		
		for (final var route : routes) {
			final var handler = createHandler(route);
			
			add(route, handler);
			
			log.info("Registered: {} {} -> {} [{} -> {}]", route.getHttpMethod(), route.getPath(), route.getMethod(), route.getConsume(), route.getProduce());
		}
		
		return container;
	}
	
	public RouteHandler createHandler(Route route) {
		final var argumentResolvers = getArgumentResolvers(route);
		
		return new RouteHandler(route, argumentResolvers, configuration);
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
	
	public void add(Route route, RouteHandler handler) {
		final var method = route.getHttpMethod();
		final var path = route.getPath().replaceAll("\\{(.+?)\\}", ":$1");
		
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
		
		routes.add(route);
	}
	
	@Controller
	@RequestMapping(path = "*")
	public static class FallbackController {
		
		@GetMapping
		public void index(Request request) {
			throw new RouteNotFoundException(request.pathInfo());
		}
		
	}
	
}