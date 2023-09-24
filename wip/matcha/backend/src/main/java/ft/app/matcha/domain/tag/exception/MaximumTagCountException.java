package ft.app.matcha.domain.tag.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.CONFLICT_409)
@SuppressWarnings("serial")
public class MaximumTagCountException extends RuntimeException {
	
	@Getter
	@ResponseErrorProperty
	private final long max;
	
	public MaximumTagCountException(long max) {
		super("maximum tag count reached");
		
		this.max = max;
	}
	
}