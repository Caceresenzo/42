package ft.framework.validation.constraint.validator.empty;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class NotEmptyStringValidatorTest {
	
	static NotEmptyStringValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new NotEmptyStringValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(validator.isValid(null));
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid(" "));
		assertTrue(validator.isValid("a"));
		
		assertFalse(validator.isValid(""));
	}
	
}