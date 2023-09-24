package ft.app.matcha.domain.message.event;

import ft.app.matcha.domain.message.Message;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
public class MessageCreatedEvent extends ApplicationEvent {
	
	@Getter
	private final Message message;
	
	public MessageCreatedEvent(Object source, Message message) {
		super(source);
		
		this.message = message;
	}
	
}