package ft.framework.mvc.handler.resolve.impl;

import java.lang.reflect.Parameter;

import ft.framework.mvc.handler.resolve.HandlerMethodArgumentResolver;
import spark.Request;
import spark.Response;

public class ParameterHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	@Override
	public boolean supportsParameter(Parameter method) {
		return method.getDeclaredAnnotation(ft.framework.mvc.annotation.Parameter.class) != null;
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var annotation = parameter.getDeclaredAnnotation(ft.framework.mvc.annotation.Parameter.class);
		
		final var name = annotation.name();
		
		final var value = request.params(name);
		
		if (value == null) {
			throw new Exception(String.format("missing `%s`", name));
		}
		
		return value;
	}
	
}