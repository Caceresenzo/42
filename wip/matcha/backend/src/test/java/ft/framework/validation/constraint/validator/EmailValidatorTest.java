package ft.framework.validation.constraint.validator;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class EmailValidatorTest {
	
	static EmailValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new EmailValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(validator.isValid(null));
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid("hello@example.com"));
		
		assertFalse(validator.isValid("helloexample.com"));
	}
	
}