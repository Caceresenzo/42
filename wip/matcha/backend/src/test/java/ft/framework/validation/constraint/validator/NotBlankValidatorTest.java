package ft.framework.validation.constraint.validator;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class NotBlankValidatorTest {
	
	static NotBlankValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new NotBlankValidator();
	}
	
	@Test
	void isValid_null() {
		assertFalse(validator.isValid(null));
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid("a"));
		assertTrue(validator.isValid(" a"));
		
		assertFalse(validator.isValid(""));
		assertFalse(validator.isValid(" "));
	}
	
}