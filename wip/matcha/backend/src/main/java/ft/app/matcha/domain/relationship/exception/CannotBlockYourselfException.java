package ft.app.matcha.domain.relationship.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
public class CannotBlockYourselfException extends RuntimeException {
	
	public CannotBlockYourselfException() {
		super("you cannot block yourself");
	}
	
}