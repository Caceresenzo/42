package ft.framework.mvc.security;

import ft.framework.mvc.filter.Filter;
import spark.Request;
import spark.Response;
import spark.utils.StringUtils;

public abstract class AuthenticationFilter implements Filter {
	
	public static final String AUTHORIZATION_HEADER = "Authorization";
	public static final String AUTHENTICATION_ATTRIBUTE = AuthenticationFilter.class.getSimpleName() + ".authentication";
	
	@Override
	public void preProcess(Request request, Response response) {
		final var authorization = request.headers(AUTHORIZATION_HEADER);
		
		Authentication authentication = null;
		
		if (StringUtils.isNotBlank(authorization)) {
			authentication = authenticate(authorization);
		}
		
		if (authentication == null) {
			authentication = AnonymousAuthentication.INSTANCE;
		}
		
		setAuthentication(request, authentication);
	}
	
	public abstract Authentication authenticate(String authorization);
	
	public static void setAuthentication(Request request, Authentication authentication) {
		request.attribute(AUTHENTICATION_ATTRIBUTE, authentication);
	}
	
	public static Authentication getAuthentication(Request request) {
		return request.attribute(AUTHENTICATION_ATTRIBUTE);
	}
	
}