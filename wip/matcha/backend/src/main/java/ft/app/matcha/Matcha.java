package ft.app.matcha;

import java.lang.annotation.Annotation;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Optional;
import java.util.function.Consumer;

import org.apache.commons.lang3.reflect.MethodUtils;

import com.fasterxml.jackson.databind.ObjectMapper;

import ft.app.matcha.controller.UserController;
import ft.framework.convert.service.SimpleConvertionService;
import ft.framework.mvc.annotation.ResponseStatus;
import ft.framework.mvc.annotation.RestController;
import ft.framework.mvc.handler.resolve.HandlerMethodArgumentResolver;
import ft.framework.mvc.handler.resolve.impl.BodyHandlerMethodArgumentResolver;
import ft.framework.mvc.handler.resolve.impl.ParameterHandlerMethodArgumentResolver;
import ft.framework.mvc.handler.resolve.impl.QueryHandlerMethodArgumentResolver;
import ft.framework.mvc.handler.resolve.impl.RequestHandlerMethodArgumentResolver;
import ft.framework.mvc.handler.resolve.impl.ResponseHandlerMethodArgumentResolver;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.route.HttpMethod;

@Slf4j
public class Matcha {
	
	@SneakyThrows
	public static void main(String[] args) {
		final var container = new UserController();
		
		registerMappings(container);
		
		Spark.exception(Exception.class, (exception, request, response) -> {
			response.body(exception.getMessage());
		});
	}
	
	public static String extractRoot(Object container) {
		final var restMapping = container.getClass().getDeclaredAnnotation(RestController.class);
		if (restMapping == null) {
			return "/";
		}
		
		return restMapping.path();
	}
	
	public static Optional<Consumer<Response>> extractResponseStatus(Method method) {
		final var annotation = method.getDeclaredAnnotation(ResponseStatus.class);
		
		if (annotation == null) {
			return Optional.empty();
		}
		
		final var status = annotation.value();
		return Optional.of((response) -> response.status(status.getCode()));
	}
	
	@SneakyThrows
	public static <T extends Annotation> void registerMappings(Object container) {
		final var objectMapper = new ObjectMapper();
		
		final var root = extractRoot(container);
		
		final var resolvers = new ArrayList<HandlerMethodArgumentResolver>();
		resolvers.add(new ParameterHandlerMethodArgumentResolver());
		resolvers.add(new QueryHandlerMethodArgumentResolver());
		resolvers.add(new RequestHandlerMethodArgumentResolver());
		resolvers.add(new ResponseHandlerMethodArgumentResolver());
		resolvers.add(new BodyHandlerMethodArgumentResolver(objectMapper));
		
		final var conversionService = new SimpleConvertionService();
		
		for (final var method : container.getClass().getDeclaredMethods()) {
			for (final var annotation : method.getDeclaredAnnotations()) {
				final var mappingAnnotation = annotation.annotationType().getDeclaredAnnotation(RestController.class);
				if (mappingAnnotation == null) {
					continue;
				}
				
				final var pathMethod = MethodUtils.getAccessibleMethod(annotation.annotationType(), "path");
				if (pathMethod == null) {
					continue;
				}
				
				String path = (String) pathMethod.invoke(annotation);
				
				final var fullPath = String.format("%s/%s", root, path)
					.replaceAll("\\/\\/+", "/")
					.replaceFirst("\\/$", "");
				
				final var parameters = method.getParameters();
				final var requestExtractors = new HandlerMethodArgumentResolver[parameters.length];
				for (var index = 0; index < parameters.length; ++index) {
					final var parameter = parameters[index];
					
					requestExtractors[index] = resolvers.stream()
						.filter((resolver) -> resolver.supportsParameter(parameter))
						.findFirst()
						.orElseThrow(() -> new Exception());
				}
				
				final var responseCustomizers = new ArrayList<Consumer<Response>>();
				extractResponseStatus(method).ifPresent(responseCustomizers::add);
				
				final var route = new Route() {
					
					@SneakyThrows
					@Override
					public Object handle(Request request, Response response) throws Exception {
						response.type("application/json");
						
						responseCustomizers.forEach((consumer) -> consumer.accept(response));
						
						final var arguments = new Object[requestExtractors.length];
						
						for (var index = 0; index < requestExtractors.length; ++index) {
							final var parameter = parameters[index];
							final var resolver = requestExtractors[index];
							
							var resolved = resolver.resolveArgument(parameter, request, response);
							
							if (resolved != null) {
								resolved = conversionService.convert(resolved, resolved.getClass(), parameter.getType());
							}
							
							arguments[index] = resolved;
						}
						
						final var returnValue = method.invoke(container, arguments);
						return objectMapper.writeValueAsString(returnValue);
					}
					
				};
				
				final var httpMethod = mappingAnnotation.method();
				
				if (HttpMethod.get.equals(httpMethod)) {
					Spark.get(fullPath, route);
				} else if (HttpMethod.post.equals(httpMethod)) {
					Spark.post(fullPath, route);
				} else if (HttpMethod.put.equals(httpMethod)) {
					Spark.put(fullPath, route);
				} else if (HttpMethod.patch.equals(httpMethod)) {
					Spark.patch(fullPath, route);
				} else if (HttpMethod.delete.equals(httpMethod)) {
					Spark.delete(fullPath, route);
				} else {
					throw new IllegalStateException(String.format("no method for %s", httpMethod));
				}
				
				log.info("Registered: {} {} -> {}", httpMethod, fullPath, method);
			}
		}
	}
	
}