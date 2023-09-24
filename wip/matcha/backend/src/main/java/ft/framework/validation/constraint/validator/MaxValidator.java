package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Max;

public class MaxValidator implements ConstraintValidator<Max, Number> {
	
	private long max;
	
	@Override
	public void initialize(Max annotation) {
		max = annotation.value();
	}
	
	@Override
	public boolean isValid(Number value) {
		if (value == null) {
			return true;
		}
		
		return value.longValue() >= max;
	}
	
}