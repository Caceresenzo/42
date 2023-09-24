package ft.app.matcha.domain.picture.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.NOT_FOUND_404)
@SuppressWarnings("serial")
@Getter
public class PictureNotFoundException extends RuntimeException {
	
	@ResponseErrorProperty
	private final long id;
	
	public PictureNotFoundException(long id) {
		super("picture not found");
		
		this.id = id;
	}
	
}