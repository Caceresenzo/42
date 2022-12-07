package ft.app.matcha.domain.auth.event;

import ft.app.matcha.domain.auth.RefreshToken;
import lombok.Getter;

@Getter
@SuppressWarnings("serial")
public class LogoutEvent extends AuthEvent {
	
	private final RefreshToken refreshToken;
	
	public LogoutEvent(Object source, RefreshToken refreshToken) {
		super(source);
		
		this.refreshToken = refreshToken;
	}
	
}