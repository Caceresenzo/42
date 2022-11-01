package ft.framework.mvc.handler.resolve.impl;

import java.lang.reflect.Parameter;

import ft.framework.mvc.handler.resolve.HandlerMethodArgumentResolver;
import spark.Request;
import spark.Response;

public class RequestHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	@Override
	public boolean supportsParameter(Parameter method) {
		return method.getType().equals(Request.class);
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		return request;
	}
	
}