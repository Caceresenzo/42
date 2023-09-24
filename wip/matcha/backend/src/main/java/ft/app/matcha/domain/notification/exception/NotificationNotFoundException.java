package ft.app.matcha.domain.notification.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.NOT_FOUND_404)
@SuppressWarnings("serial")
@Getter
public class NotificationNotFoundException extends RuntimeException {
	
	@ResponseErrorProperty
	private final long id;
	
	public NotificationNotFoundException(long id) {
		super("notification not found");
		
		this.id = id;
	}
	
}