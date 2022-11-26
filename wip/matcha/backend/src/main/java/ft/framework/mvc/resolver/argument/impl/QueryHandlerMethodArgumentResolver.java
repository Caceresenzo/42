package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;

import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import spark.Request;
import spark.Response;

public class QueryHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	@Override
	public boolean supportsParameter(Parameter method) {
		return method.getDeclaredAnnotation(Query.class) != null;
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var annotation = parameter.getDeclaredAnnotation(Query.class);
		
		final var name = annotation.name();
		final var required = annotation.required();
		
		final var value = request.queryParams(name);
		
		if (required && value == null) {
			throw new Exception(String.format("missing `%s`", name));
		}
		
		return value;
	}
	
}