package ft.app.matcha.domain.auth.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.experimental.StandardException;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@StandardException
public class JwtException extends RuntimeException {
	
}