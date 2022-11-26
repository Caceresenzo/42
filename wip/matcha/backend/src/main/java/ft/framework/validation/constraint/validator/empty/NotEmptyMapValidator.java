package ft.framework.validation.constraint.validator.empty;

import java.util.Map;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.NotNull;

public class NotEmptyMapValidator implements ConstraintValidator<NotNull, Map<?, ?>> {

	@Override
	public boolean isValid(Map<?, ?> value) {
		if (value == null) {
			return true;
		}
		
		return !value.isEmpty();
	}
	
}