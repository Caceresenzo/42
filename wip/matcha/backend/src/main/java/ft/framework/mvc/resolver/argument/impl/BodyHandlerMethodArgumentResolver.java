package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;
import java.lang.reflect.Type;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import lombok.RequiredArgsConstructor;
import spark.Request;
import spark.Response;

@RequiredArgsConstructor
public class BodyHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	private final ObjectMapper objectMapper;
	
	@Override
	public boolean supportsParameter(Parameter method) {
		return method.getDeclaredAnnotation(Body.class) != null;
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var type = parameter.getParameterizedType();
		
		return objectMapper.readValue(request.bodyAsBytes(), new TypeReference<Object>() {
			
			@Override
			public Type getType() {
				return type;
			}
			
		});
	}
	
}