package ft.app.matcha.security;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.experimental.StandardException;

@SuppressWarnings("serial")
@StandardException
@ResponseStatus(HttpStatus.FORBIDDEN_403)
public class ForbiddenException extends RuntimeException {
	
}