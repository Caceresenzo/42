package ft.framework.validation.constraint.validator;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.annotation.Annotation;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import ft.framework.validation.constraint.annotation.Port;

class PortValidatorTest {
	
	static PortValidator validator;
	
	@BeforeAll
	static void setUp() {
		validator = new PortValidator();
	}
	
	@Test
	void isValid_null() {
		assertTrue(isValid(null, true));
		assertTrue(isValid(null, false));
	}
	
	@Test
	void isValid() {
		assertTrue(isValid(0, true));
		assertTrue(isValid(80, false));
		assertTrue(isValid(65535, false));
		
		assertFalse(isValid(0, false));
		assertFalse(isValid(65536, false));
	}
	
	boolean isValid(Integer value, boolean zero) {
		validator.initialize(new Port() {
			
			@Override
			public Class<? extends Annotation> annotationType() {
				return null;
			}
			
			@Override
			public boolean zero() {
				return zero;
			}
			
			@Override
			public String message() {
				return null;
			}
			
		});
		
		return validator.isValid(value);
	}
	
}