package ft.app.matcha.security.jwt;

import org.apache.commons.lang3.StringUtils;

import ft.framework.mvc.security.Authentication;
import ft.framework.mvc.security.AuthenticationFilter;
import lombok.RequiredArgsConstructor;
import spark.Request;
import spark.Response;

@RequiredArgsConstructor
public class JwtHeaderAuthenticationFilter extends AuthenticationFilter {
	
	public static final String AUTHORIZATION_HEADER = "Authorization";
	
	private final JwtAuthenticator jwtAuthenticator;
	
	@Override
	public Authentication authenticate(Request request, Response response) {
		final var authorizationHeaderValue = request.headers(AUTHORIZATION_HEADER);
		
		if (StringUtils.isNotBlank(authorizationHeaderValue)) {
			final var jwt = extractJwt(authorizationHeaderValue);
			return jwtAuthenticator.authenticate(jwt);
		}
		
		return null;
	}
	
	public String extractJwt(String authorizationHeaderValue) {
		final var parts = authorizationHeaderValue.split(" ", 2);
		
		if (parts.length != 2) {
			return null;
		}
		
		return parts[1];
	}
	
}