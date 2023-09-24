package ft.framework.validation.constraint.validator.empty;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Collections;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class NotEmptyCollectionValidatorTest {
	
	static NotEmptyCollectionValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new NotEmptyCollectionValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(validator.isValid(null));
	}
	
	@Test
	void isValid() {
		assertTrue(validator.isValid(Collections.singleton(1)));
		assertTrue(validator.isValid(Collections.singletonList(1)));
		
		assertFalse(validator.isValid(Collections.emptySet()));
		assertFalse(validator.isValid(Collections.emptyList()));
	}
	
}