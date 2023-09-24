package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Positive;

public class PositiveValidator implements ConstraintValidator<Positive, Number> {
	
	@Override
	public boolean isValid(Number value) {
		if (value == null) {
			return true;
		}
		
		return value.longValue() > 0;
	}
	
}