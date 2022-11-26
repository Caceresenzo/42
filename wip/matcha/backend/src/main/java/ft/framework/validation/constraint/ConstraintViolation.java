package ft.framework.validation.constraint;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class ConstraintViolation<T> {
	
	private final String message;
	private final String propertyPath;
	private final Object rejectedValue;
	
}