package ft.framework.validation.constraint.validator;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class NotNullValidatorTest {
	
	static NotNullValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new NotNullValidator();
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid(""));
		assertFalse(validator.isValid(null));
	}
	
}