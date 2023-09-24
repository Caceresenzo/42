package ft.app.matcha.domain.relationship.event;

import ft.app.matcha.domain.user.User;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
public class UnlikedEvent extends ApplicationEvent {
	
	private final User user;
	private final User peer;
	
	public UnlikedEvent(Object source, User user, User peer) {
		super(source);
		
		this.user = user;
		this.peer = peer;
	}
	
}