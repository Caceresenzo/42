package ft.app.matcha.domain.report.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
public class CannotReportYourselfException extends RuntimeException {
	
	public CannotReportYourselfException() {
		super("you cannot report yourself");
	}
	
}