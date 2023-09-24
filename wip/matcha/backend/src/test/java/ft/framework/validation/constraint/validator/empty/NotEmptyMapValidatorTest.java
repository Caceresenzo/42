package ft.framework.validation.constraint.validator.empty;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Collections;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class NotEmptyMapValidatorTest {
	
	static NotEmptyMapValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new NotEmptyMapValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(validator.isValid(null));
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid(Collections.singletonMap(1, 1)));
		assertFalse(validator.isValid(Collections.emptyMap()));
	}
	
}