package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;

import org.apache.commons.lang3.StringUtils;

import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import spark.Request;
import spark.Response;

public class VariableHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	@Override
	public boolean supportsParameter(Parameter parameter) {
		return parameter.getDeclaredAnnotation(Variable.class) != null;
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var annotation = parameter.getDeclaredAnnotation(Variable.class);
		
		var name = annotation.name();
		if (StringUtils.isEmpty(name)) {
			name = parameter.getName();
		}
		
		final var value = request.params(name);
		
		if (value == null) {
			throw new Exception(String.format("missing `%s`", name));
		}
		
		return value;
	}
	
}