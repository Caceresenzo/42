package ft.framework.validation;

import java.util.Set;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import ft.framework.validation.constraint.ConstraintViolation;
import lombok.Getter;

@SuppressWarnings("serial")
@ResponseStatus(HttpStatus.BAD_REQUEST_400)
public class ValidationException extends RuntimeException {
	
	@Getter
	@ResponseErrorProperty
	private final Set<ConstraintViolation<?>> violations;
	
	public ValidationException(Set<ConstraintViolation<?>> violations) {
		this.violations = violations;
	}
	
}