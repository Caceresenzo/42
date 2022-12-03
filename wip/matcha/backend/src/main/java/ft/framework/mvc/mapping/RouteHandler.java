package ft.framework.mvc.mapping;

import java.lang.reflect.InvocationTargetException;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;
import java.util.function.Consumer;

import javax.servlet.http.HttpServletResponse;

import ft.framework.mvc.MvcConfiguration;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import ft.framework.validation.ValidationException;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.ConstraintViolation;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;
import spark.Request;
import spark.Response;

@RequiredArgsConstructor
public class RouteHandler implements spark.Route {
	
	private final Route route;
	private final HandlerMethodArgumentResolver[] argumentResolvers;
	private final List<Consumer<Response>> responseCustomizers;
	private final MvcConfiguration mvcConfiguration;
	
	@Override
	public Object handle(Request request, Response response) throws Exception {
		final var arguments = resolveAndValidateArguments(request, response);
		
		final var returnValue = invokeMethod(arguments);
		
		applyCustomizations(response);
		
		return convertResponse(response, returnValue);
	}
	
	@SneakyThrows
	public HttpServletResponse convertResponse(Response response, Object returnValue) {
		final var service = mvcConfiguration.getHttpMessageConversionService();
		
		final var servletResponse = response.raw();
		final var outputStream = servletResponse.getOutputStream();
		
		service.write(returnValue, route.getMethod().getReturnType(), route.getProduce(), outputStream);
		
		outputStream.flush();
		outputStream.close();
		
		return servletResponse;
	}
	
	public Object[] resolveAndValidateArguments(Request request, Response response) {
		final var arguments = resolveArguments(request, response);
		
		final var violations = validate(arguments);
		if (!violations.isEmpty()) {
			throw new ValidationException(violations);
		}
		
		return arguments;
	}
	
	@SneakyThrows
	public Object invokeMethod(Object[] arguments) {
		try {
			return route.getMethod().invoke(route.getContainer(), arguments);
		} catch (InvocationTargetException exception) {
			throw exception.getCause();
		}
	}
	
	public void applyCustomizations(Response response) {
		responseCustomizers.forEach((consumer) -> consumer.accept(response));
	}
	
	@SneakyThrows
	public Object[] resolveArguments(Request request, Response response) {
		final var parameters = route.getParameters();
		
		final var arguments = new Object[parameters.size()];
		for (var index = 0; index < argumentResolvers.length; ++index) {
			final var parameter = parameters.get(index);
			final var resolver = argumentResolvers[index];
			
			var resolved = resolver.resolveArgument(parameter, request, response);
			
			if (resolved != null) {
				resolved = mvcConfiguration.getConversionService().convert(resolved, resolved.getClass(), parameter.getType());
			}
			
			arguments[index] = resolved;
		}
		
		return arguments;
	}
	
	public Set<ConstraintViolation<?>> validate(Object[] arguments) {
		final var parameters = route.getParameters();
		
		final var violations = new LinkedHashSet<ConstraintViolation<?>>();
		
		for (var index = 0; index < argumentResolvers.length; ++index) {
			final var parameter = parameters.get(index);
			final var value = arguments[index];
			
			if (parameter.getAnnotation(Valid.class) != null) {
				violations.addAll(mvcConfiguration.getValidator().validate(value));
			}
		}
		
		return violations;
	}
	
}