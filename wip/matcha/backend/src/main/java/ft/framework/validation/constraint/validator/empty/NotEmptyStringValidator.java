package ft.framework.validation.constraint.validator.empty;

import org.apache.commons.lang3.StringUtils;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.NotNull;

public class NotEmptyStringValidator implements ConstraintValidator<NotNull, CharSequence> {

	@Override
	public boolean isValid(CharSequence value) {
		if (value == null) {
			return true;
		}
		
		return StringUtils.isNotEmpty(value);
	}
	
}