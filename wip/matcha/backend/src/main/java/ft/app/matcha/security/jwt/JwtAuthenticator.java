package ft.app.matcha.security.jwt;

import ft.app.matcha.domain.auth.JwtService;
import ft.app.matcha.security.UserAuthentication;
import ft.framework.mvc.security.Authentication;
import lombok.RequiredArgsConstructor;
import spark.utils.StringUtils;

@RequiredArgsConstructor
public class JwtAuthenticator {
	
	private final JwtService jwtService;
	
	public Authentication authenticate(String token) {
		if (StringUtils.isBlank(token)) {
			return null;
		}
		
		final var user = jwtService.decode(token);
		if (user == null) {
			return null;
		}
		
		return new UserAuthentication(user);
	}
	
}