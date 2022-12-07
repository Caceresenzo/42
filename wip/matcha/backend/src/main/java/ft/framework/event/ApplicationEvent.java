package ft.framework.event;

import java.time.Clock;
import java.time.LocalDateTime;
import java.util.EventObject;

import lombok.Getter;

@Getter
@SuppressWarnings("serial")
public abstract class ApplicationEvent extends EventObject {
	
	private final LocalDateTime timestamp;
	
	public ApplicationEvent(Object source) {
		this(source, LocalDateTime.now());
	}
	
	public ApplicationEvent(Object source, Clock clock) {
		this(source, LocalDateTime.now(clock));
	}
	
	private ApplicationEvent(Object source, LocalDateTime timestamp) {
		super(source);
		
		this.timestamp = timestamp;
	}
	
}