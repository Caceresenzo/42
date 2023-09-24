package ft.framework.mvc.security;

import ft.framework.mvc.filter.Filter;
import spark.Request;
import spark.Response;

public abstract class AuthenticationFilter implements Filter {
	
	public static final String AUTHENTICATION_ATTRIBUTE = AuthenticationFilter.class.getSimpleName() + ".authentication";
	
	@Override
	public void preProcess(Request request, Response response) {
		Authentication authentication = authenticate(request, response);
		
		if (authentication == null) {
			authentication = AnonymousAuthentication.INSTANCE;
		}
		
		setAuthentication(request, authentication);
	}
	
	public abstract Authentication authenticate(Request request, Response response);
	
	public static void setAuthentication(Request request, Authentication authentication) {
		request.attribute(AUTHENTICATION_ATTRIBUTE, authentication);
	}
	
	public static Authentication getAuthentication(Request request) {
		return request.attribute(AUTHENTICATION_ATTRIBUTE);
	}
	
}