package ft.app.matcha.domain.tag.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.NOT_FOUND_404)
@SuppressWarnings("serial")
@Getter
public class TagNotFoundException extends RuntimeException {
	
	@ResponseErrorProperty
	private final long id;
	
	public TagNotFoundException(long id) {
		super("tag not found");
		
		this.id = id;
	}
	
}