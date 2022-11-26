package ft.framework.validation;

import java.util.Set;

import ft.framework.validation.constraint.ConstraintViolation;

public class ValidationException extends RuntimeException {

	public ValidationException(Set<ConstraintViolation<?>> violations) {
		violations.forEach(System.out::println);
	}
	
}