package ft.framework.validation.constraint.validator.empty;

import java.util.Collection;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.NotNull;

public class NotEmptyCollectionValidator implements ConstraintValidator<NotNull, Collection<?>> {

	@Override
	public boolean isValid(Collection<?> value) {
		if (value == null) {
			return true;
		}
		
		return !value.isEmpty();
	}
	
}