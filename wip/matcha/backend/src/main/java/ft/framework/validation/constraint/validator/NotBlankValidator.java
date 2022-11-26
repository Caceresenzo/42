package ft.framework.validation.constraint.validator;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.NotBlank;
import spark.utils.StringUtils;

public class NotBlankValidator implements ConstraintValidator<NotBlank, CharSequence> {

	@Override
	public boolean isValid(CharSequence value) {
		return StringUtils.isNotBlank(value);
	}
	
}