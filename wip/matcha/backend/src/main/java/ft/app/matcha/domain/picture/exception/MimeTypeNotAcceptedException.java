package ft.app.matcha.domain.picture.exception;

import java.util.List;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.BAD_REQUEST_400)
@SuppressWarnings("serial")
@Getter
public class MimeTypeNotAcceptedException extends RuntimeException {
	
	@ResponseErrorProperty
	private final String mimeType;
	
	@ResponseErrorProperty
	private final List<String> acceptedMimeTypes;
	
	public MimeTypeNotAcceptedException(String mimeType, List<String> acceptedMimeTypes) {
		super("format not accepted");
		
		this.mimeType = mimeType;
		this.acceptedMimeTypes = acceptedMimeTypes;
	}
	
}