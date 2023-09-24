package ft.app.matcha.domain.auth.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@Getter
public class SameEmailException extends RuntimeException {
	
	public SameEmailException() {
		super("email same as current one");
	}
	
}