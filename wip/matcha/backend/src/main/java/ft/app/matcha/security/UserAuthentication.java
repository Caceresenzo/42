package ft.app.matcha.security;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.security.Authentication;
import lombok.Data;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

@Data
@RequiredArgsConstructor
public class UserAuthentication implements Authentication {
	
	@NonNull
	private final User user;
	private boolean authenticated = true;
	
	@Override
	public String getName() {
		return user.getName();
	}
	
	@Override
	public Object getPrincipal() {
		return user;
	}
	
}