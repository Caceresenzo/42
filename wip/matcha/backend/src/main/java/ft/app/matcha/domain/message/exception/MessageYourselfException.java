package ft.app.matcha.domain.message.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.experimental.StandardException;

@SuppressWarnings("serial")
@StandardException
@ResponseStatus(HttpStatus.CONFLICT_409)
public class MessageYourselfException extends RuntimeException {
	
	public MessageYourselfException() {
		super("you cannot send message to yourself");
	}
	
}