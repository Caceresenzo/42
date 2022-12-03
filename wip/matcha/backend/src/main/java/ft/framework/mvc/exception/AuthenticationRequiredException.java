package ft.framework.mvc.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
@ResponseStatus(HttpStatus.UNAUTHORIZED_401)
public class AuthenticationRequiredException extends RuntimeException {
	
	public AuthenticationRequiredException() {
		super("not authenticated");
	}
	
}