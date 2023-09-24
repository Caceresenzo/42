package ft.app.matcha.domain.picture.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@Getter
public class InvalidPictureOwnerException extends RuntimeException {
	
	@ResponseErrorProperty
	private final long id;
	
	public InvalidPictureOwnerException(long id) {
		super("picture owner is not you");
		
		this.id = id;
	}
	
}