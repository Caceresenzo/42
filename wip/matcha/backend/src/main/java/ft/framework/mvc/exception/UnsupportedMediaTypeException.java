package ft.framework.mvc.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
@ResponseStatus(HttpStatus.UNSUPPORTED_MEDIA_TYPE_415)
public class UnsupportedMediaTypeException extends RuntimeException {

	@ResponseErrorProperty
	private final String mediaType;
	
	public UnsupportedMediaTypeException(String mediaType) {
		super("unsupported media type");
		
		this.mediaType = mediaType;
	}
	
}