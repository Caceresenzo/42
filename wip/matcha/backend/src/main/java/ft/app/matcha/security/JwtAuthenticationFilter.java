package ft.app.matcha.security;

import ft.app.matcha.domain.auth.JwtService;
import ft.framework.mvc.security.Authentication;
import ft.framework.mvc.security.AuthenticationFilter;
import lombok.RequiredArgsConstructor;
import spark.utils.StringUtils;

@RequiredArgsConstructor
public class JwtAuthenticationFilter extends AuthenticationFilter {
	
	private final JwtService jwtService;
	
	@Override
	public Authentication authenticate(String authorization) {
		final var jwt = getJwt(authorization);
		if (StringUtils.isBlank(jwt)) {
			return null;
		}
		
		final var user = jwtService.decode(jwt);
		return new UserAuthentication(user);
	}
	
	public String getJwt(String authorization) {
		final var parts = authorization.split(" ", 2);
		
		if (parts.length != 2) {
			return null;
		}
		
		return parts[1];
	}
	
}