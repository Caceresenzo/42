package ft.app.matcha.domain.auth.event;

import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
public class AuthEvent extends ApplicationEvent {
	
	public AuthEvent(Object source) {
		super(source);
	}
	
}