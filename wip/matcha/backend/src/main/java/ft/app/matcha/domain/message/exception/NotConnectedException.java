package ft.app.matcha.domain.message.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.experimental.StandardException;

@SuppressWarnings("serial")
@StandardException
@ResponseStatus(HttpStatus.FAILED_DEPENDENCY_424)
public class NotConnectedException extends RuntimeException {
	
	public NotConnectedException() {
		super("you must be connected to send him/her a message");
	}
	
}