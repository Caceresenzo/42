package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Positive;

public class PositiveValidator implements ConstraintValidator<Positive, Integer> {
	
	@Override
	public boolean isValid(Integer value) {
		if (value == null) {
			return true;
		}
		
		return value.intValue() > 0;
	}
	
}