package ft.app.matcha.domain.visit.event;

import ft.app.matcha.domain.visit.Visit;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@SuppressWarnings("serial")
public class VisitedEvent extends ApplicationEvent {
	
	@Getter
	private final Visit visit;
	
	public VisitedEvent(Object source, Visit visit) {
		super(source);
		
		this.visit = visit;
	}
	
}