package ft.app.matcha.domain.auth.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@Getter
public class InvalidConfirmPasswordException extends RuntimeException {
	
	public InvalidConfirmPasswordException() {
		super("confirm password does not match");
	}
	
}