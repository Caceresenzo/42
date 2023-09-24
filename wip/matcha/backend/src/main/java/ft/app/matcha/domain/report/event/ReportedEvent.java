package ft.app.matcha.domain.report.event;

import ft.app.matcha.domain.report.Report;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@Getter
@SuppressWarnings("serial")
public class ReportedEvent extends ApplicationEvent {
	
	private final Report report;
	
	public ReportedEvent(Object source, Report report) {
		super(source);
		
		this.report = report;
	}
	
}