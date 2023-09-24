package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;
import java.net.InetAddress;

import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import spark.Request;
import spark.Response;

public class InetAddressHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	@Override
	public boolean supportsParameter(Parameter parameter) {
		return InetAddress.class.equals(parameter.getType());
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		return InetAddress.getByName(request.raw().getRemoteAddr());
	}
	
}