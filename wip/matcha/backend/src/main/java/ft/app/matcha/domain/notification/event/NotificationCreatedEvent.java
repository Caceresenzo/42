package ft.app.matcha.domain.notification.event;

import ft.app.matcha.domain.notification.Notification;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
public class NotificationCreatedEvent extends ApplicationEvent {
	
	@Getter
	private final Notification notification;
	
	public NotificationCreatedEvent(Object source, Notification notification) {
		super(source);
		
		this.notification = notification;
	}
	
}