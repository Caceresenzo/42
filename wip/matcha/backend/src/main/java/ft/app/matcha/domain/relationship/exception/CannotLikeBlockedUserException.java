package ft.app.matcha.domain.relationship.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseStatus;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
public class CannotLikeBlockedUserException extends RuntimeException {
	
	public CannotLikeBlockedUserException() {
		super("you cannot like an user you blocked");
	}
	
}