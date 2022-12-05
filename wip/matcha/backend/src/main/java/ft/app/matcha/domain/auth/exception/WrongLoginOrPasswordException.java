package ft.app.matcha.domain.auth.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
public class WrongLoginOrPasswordException extends RuntimeException {
	
	public WrongLoginOrPasswordException() {
		super("wrong login or password");
	}
	
}