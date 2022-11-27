package ft.app.matcha;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.Optional;
import java.util.function.Consumer;

import org.apache.commons.lang3.reflect.MethodUtils;
import org.eclipse.jetty.http.HttpStatus;

import com.fasterxml.jackson.databind.ObjectMapper;

import ft.app.matcha.controller.UserController;
import ft.framework.convert.service.SimpleConvertionService;
import ft.framework.mvc.annotation.ResponseStatus;
import ft.framework.mvc.annotation.RestController;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.BodyHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.ParameterHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.QueryHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.RequestHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.argument.impl.ResponseHandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.exception.DefaultHandlerExceptionResolver;
import ft.framework.validation.ValidationException;
import ft.framework.validation.Validator;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.ConstraintViolation;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import spark.ExceptionHandler;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.route.HttpMethod;

@Slf4j
public class Matcha {
	
	@SneakyThrows
	public static void main(String[] args) {
		final var objectMapper = new ObjectMapper();
		
		final var exceptionResolver = new DefaultHandlerExceptionResolver();
		final var container = new UserController();
		
		registerMappings(container);
		
		Spark.exception(Exception.class, new ExceptionHandler<Exception>() {
			
			@SneakyThrows
			@Override
			public void handle(Exception exception, Request request, Response response) {
				final var problem = exceptionResolver.resolveException(request.raw(), response.raw(), exception);
				
				final var status = problem.getStatus();
				if (status != null) {
					response.status(status);
				} else {
					response.status(HttpStatus.INTERNAL_SERVER_ERROR_500);
				}
				
				response.body(objectMapper.writeValueAsString(problem));
				
				if (response.status() == HttpStatus.INTERNAL_SERVER_ERROR_500) {
					log.error("Could not process request", exception);
				}
			}
			
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
		return Optional.of((response) -> response.status(status));
	}
	
	@SneakyThrows
	public static void registerMappings(Object container) {
		final var objectMapper = new ObjectMapper();
		
		final var root = extractRoot(container);
		
		final var resolvers = new ArrayList<HandlerMethodArgumentResolver>();
		resolvers.add(new ParameterHandlerMethodArgumentResolver());
		resolvers.add(new QueryHandlerMethodArgumentResolver());
		resolvers.add(new RequestHandlerMethodArgumentResolver());
		resolvers.add(new ResponseHandlerMethodArgumentResolver());
		resolvers.add(new BodyHandlerMethodArgumentResolver(objectMapper));
		
		final var conversionService = new SimpleConvertionService();
		final var validator = new Validator();
		
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
						
						final var violations = new LinkedHashSet<ConstraintViolation<?>>();
						for (var index = 0; index < requestExtractors.length; ++index) {
							final var parameter = parameters[index];
							final var value = arguments[index];
							
							if (parameter.getAnnotation(Valid.class) != null) {
								violations.addAll(validator.validate(value));
							}
						}
						
						if (!violations.isEmpty()) {
							throw new ValidationException(violations);
						}
						
						try {
							final var returnValue = method.invoke(container, arguments);
							return objectMapper.writeValueAsString(returnValue);
						} catch (InvocationTargetException exception) {
							throw exception.getCause();
						}
						
					}
					
				};
				
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