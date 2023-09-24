package ft.app.matcha.domain.user.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@Getter
public class OnlyYourselfException extends RuntimeException {
	
	public OnlyYourselfException() {
		super("you can only do this on yourself");
	}
	
}