package ft.app.matcha.domain.auth.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.experimental.StandardException;

@ResponseStatus(HttpStatus.UNAUTHORIZED_401)
@SuppressWarnings("serial")
@StandardException
public class JwtExpiredException extends JwtException {
	
	public static final String MESSAGE = "signature is expired";
	
	public JwtExpiredException() {
		super(MESSAGE);
	}
	
	public JwtExpiredException(Throwable cause) {
		super(MESSAGE, cause);
	}
	
}