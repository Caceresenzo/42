package ft.app.matcha.domain.notification.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@Getter
public class InvalidNotificationOwnerException extends RuntimeException {
	
	@ResponseErrorProperty
	private final long id;
	
	public InvalidNotificationOwnerException(long id) {
		super("notification owner is not you");
		
		this.id = id;
	}
	
}