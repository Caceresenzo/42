package ft.app.matcha.domain.heartbeat.event;

import ft.app.matcha.domain.heartbeat.Heartbeat;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
public class HeartbeatEvent extends ApplicationEvent {
	
	@Getter
	private final Heartbeat heartbeat;
	
	public HeartbeatEvent(Object source, Heartbeat heartbeat) {
		super(source);
		
		this.heartbeat = heartbeat;
	}
	
}