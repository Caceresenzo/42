package ft.framework.convert.service;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@SuppressWarnings("serial")
@ResponseStatus(HttpStatus.BAD_REQUEST_400)
@Getter
public class ConversionException extends RuntimeException {
	
	@ResponseErrorProperty
	private final Object value;
	
	@ResponseErrorProperty
	private final Class<?> sourceType;
	
	@ResponseErrorProperty
	private final Class<?> targetType;

	public ConversionException(Object value, Class<?> sourceType, Class<?> targetType, Throwable cause) {
		super("could not convert `%s` to target type `%s`".formatted(value, targetType.getSimpleName()), cause);
		
		this.value = value;
		this.sourceType = sourceType;
		this.targetType = targetType;
	}
	
	
}