package ft.framework.mvc.resolver.argument;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.experimental.StandardException;

@SuppressWarnings("serial")
@StandardException
@ResponseStatus(HttpStatus.BAD_REQUEST_400)
public class MissingArgumentException extends RuntimeException {
	
}