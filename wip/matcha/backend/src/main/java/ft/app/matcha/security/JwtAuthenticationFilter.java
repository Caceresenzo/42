package ft.app.matcha.security;

import ft.app.matcha.entity.User;
import ft.framework.mvc.security.Authentication;
import ft.framework.mvc.security.AuthenticationFilter;

public class JwtAuthenticationFilter extends AuthenticationFilter {
	
	@Override
	public Authentication authenticate(String authorization) {
		// TODO Implement real JWT parsing
		return new UserAuthentication(new User().setName(authorization));
	}
	
}