package ft.app.matcha.domain.relationship.event;

import ft.app.matcha.domain.user.User;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
public class LikedEvent extends ApplicationEvent {
	
	private final User user;
	private final User peer;
	private final boolean cross;
	
	public LikedEvent(Object source, User user, User peer, boolean cross) {
		super(source);
		
		this.user = user;
		this.peer = peer;
		this.cross = cross;
	}
	
}