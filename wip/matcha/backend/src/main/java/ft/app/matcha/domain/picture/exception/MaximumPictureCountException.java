package ft.app.matcha.domain.picture.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
public class MaximumPictureCountException extends RuntimeException {
	
	@Getter
	@ResponseErrorProperty
	private final long max;
	
	public MaximumPictureCountException(long max) {
		super("maximum picture count reached");
		
		this.max = max;
	}
	
}