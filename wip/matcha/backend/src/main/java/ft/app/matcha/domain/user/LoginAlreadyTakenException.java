package ft.app.matcha.domain.user;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
@Getter
public class LoginAlreadyTakenException extends RuntimeException {
	
	@ResponseErrorProperty
	private final String login;
	
	public LoginAlreadyTakenException(String login) {
		super("login already taken");
		
		this.login = login;
	}
	
}