package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Port;

public class PortValidator implements ConstraintValidator<Port, Integer> {
	
	private boolean zero;
	
	@Override
	public void initialize(Port annotation) {
		zero = annotation.zero();
	}
	
	@Override
	public boolean isValid(Integer value) {
		if (value == null) {
			return true;
		}
		
		if (zero && value == 0) {
			return true;
		}
		
		return value > 0 && value <= 65535;
	}
	
}