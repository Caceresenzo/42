package ft.framework.validation.constraint.validator;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.annotation.Annotation;
import java.util.OptionalInt;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import ft.framework.validation.constraint.annotation.Length;

class LengthValidatorTest {
	
	static LengthValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new LengthValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(isValid(null, OptionalInt.empty(), OptionalInt.empty()));
		assertTrue(isValid(null, OptionalInt.of(1), OptionalInt.of(1)));
	}
	
	@Test
	void isValid() {
		assertTrue(isValid("", OptionalInt.empty(), OptionalInt.empty()));
		assertTrue(isValid("", OptionalInt.empty(), OptionalInt.of(1)));
		assertTrue(isValid(" ", OptionalInt.empty(), OptionalInt.of(1)));
		assertTrue(isValid(" ", OptionalInt.of(1), OptionalInt.of(1)));
		assertTrue(isValid(" ", OptionalInt.of(1), OptionalInt.empty()));
		assertTrue(isValid("  ", OptionalInt.of(2), OptionalInt.empty()));

		assertFalse(isValid("", OptionalInt.of(1), OptionalInt.empty()));
		assertFalse(isValid("  ", OptionalInt.empty(), OptionalInt.of(1)));
	}
	
	boolean isValid(String value, OptionalInt min, OptionalInt max) {
		validator.initialize(new Length() {
			
			@Override
			public Class<? extends Annotation> annotationType() {
				return null;
			}
			
			@Override
			public int min() {
				return min.orElse(Length.UNSPECIFIED);
			}
			
			@Override
			public String message() {
				return null;
			}
			
			@Override
			public int max() {
				return max.orElse(Length.UNSPECIFIED);
			}
			
		});
		
		return validator.isValid(value);
	}
	
}