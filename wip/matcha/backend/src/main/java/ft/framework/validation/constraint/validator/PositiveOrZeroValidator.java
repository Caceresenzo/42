package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.PositiveOrZero;

public class PositiveOrZeroValidator implements ConstraintValidator<PositiveOrZero, Number> {
	
	@Override
	public boolean isValid(Number value) {
		if (value == null) {
			return true;
		}
		
		return value.intValue() >= 0;
	}
	
}