package ft.app.matcha.domain.auth.event;

import ft.app.matcha.domain.user.User;
import lombok.Getter;

@Getter
@SuppressWarnings("serial")
public class LoginEvent extends AuthEvent {
	
	private final User user;
	
	public LoginEvent(Object source, User user) {
		super(source);
		
		this.user = user;
	}
	
}