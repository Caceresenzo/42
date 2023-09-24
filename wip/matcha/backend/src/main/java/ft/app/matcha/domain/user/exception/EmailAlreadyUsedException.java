package ft.app.matcha.domain.user.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
@Getter
public class EmailAlreadyUsedException extends RuntimeException {
	
	@ResponseErrorProperty
	private final String email;
	
	public EmailAlreadyUsedException(String email) {
		super("email already used");
		
		this.email = email;
	}
	
}