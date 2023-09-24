package ft.framework.validation.constraint.validator;

import java.util.regex.Pattern;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Email;

public class EmailValidator implements ConstraintValidator<Email, String> {
	
	/** https://stackoverflow.com/a/201378/7292958 */
	public static final Pattern PATTERN = Pattern.compile("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])");
	
	@Override
	public boolean isValid(String value) {
		if (value == null) {
			return true;
		}
		
		final var matcher = PATTERN.matcher(value);
		if (!matcher.find()) {
			return false;
		}
		
		return matcher.hitEnd();
	}
	
}