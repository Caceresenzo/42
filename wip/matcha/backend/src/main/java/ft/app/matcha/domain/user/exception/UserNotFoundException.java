package ft.app.matcha.domain.user.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.NOT_FOUND_404)
@SuppressWarnings("serial")
@Getter
public class UserNotFoundException extends RuntimeException {
	
	@ResponseErrorProperty
	private final long id;
	
	public UserNotFoundException(long id) {
		super("user not found");
		
		this.id = id;
	}
	
}