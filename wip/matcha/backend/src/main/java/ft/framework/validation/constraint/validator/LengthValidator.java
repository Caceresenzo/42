package ft.framework.validation.constraint.validator;

import java.util.OptionalInt;

import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.annotation.Length;

public class LengthValidator implements ConstraintValidator<Length, String> {
	
	private OptionalInt min;
	private OptionalInt max;
	
	@Override
	public void initialize(Length annotation) {
		min = ifNotDefault(annotation.min());
		max = ifNotDefault(annotation.max());
	}
	
	@Override
	public boolean isValid(String value) {
		if (value == null) {
			return true;
		}
		
		if (min.isPresent() && min.getAsInt() > value.length()) {
			return false;
		}
		
		if (max.isPresent() && max.getAsInt() < value.length()) {
			return false;
		}
		
		return false;
	}
	
	public static OptionalInt ifNotDefault(int value) {
		if (value == Length.UNSPECIFIED) {
			return OptionalInt.empty();
		}
		
		return OptionalInt.of(value);
	}
	
}