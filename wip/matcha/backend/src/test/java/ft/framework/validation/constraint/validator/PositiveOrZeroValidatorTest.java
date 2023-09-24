package ft.framework.validation.constraint.validator;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class PositiveOrZeroValidatorTest {
	
	static PositiveOrZeroValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new PositiveOrZeroValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(validator.isValid(null));
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid(0));
		assertTrue(validator.isValid(0.0));
		assertTrue(validator.isValid(-0.0));
		
		assertTrue(validator.isValid(1));
		assertTrue(validator.isValid(1.0));
		
		assertTrue(validator.isValid(Integer.MAX_VALUE));
		assertTrue(validator.isValid(Long.MAX_VALUE));
		
		assertFalse(validator.isValid(-1));
		assertFalse(validator.isValid(-1.0));
	}
	
}