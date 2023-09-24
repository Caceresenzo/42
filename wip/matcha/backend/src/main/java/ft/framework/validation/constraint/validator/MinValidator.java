package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Min;

public class MinValidator implements ConstraintValidator<Min, Number> {
	
	private long min;
	
	@Override
	public void initialize(Min annotation) {
		min = annotation.value();
	}
	
	@Override
	public boolean isValid(Number value) {
		if (value == null) {
			return true;
		}
		
		return value.longValue() >= min;
	}
	
}