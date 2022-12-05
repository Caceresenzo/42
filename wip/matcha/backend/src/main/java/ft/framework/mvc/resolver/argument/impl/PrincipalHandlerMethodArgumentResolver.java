package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;

import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import ft.framework.mvc.security.AuthenticationFilter;
import spark.Request;
import spark.Response;

public class PrincipalHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	@Override
	public boolean supportsParameter(Parameter parameter) {
		return parameter.isAnnotationPresent(Principal.class);
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var authentication = AuthenticationFilter.getAuthentication(request);
		
		if (authentication == null) {
			throw new Exception("not authenticated");
		}
		
		return authentication.getPrincipal();
	}
	
}