package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.NotNull;

public class NotNullValidator implements ConstraintValidator<NotNull, Object> {

	@Override
	public boolean isValid(Object value) {
		return value != null;
	}
	
}