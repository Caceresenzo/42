package ft.framework.convert.converter.impl;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class StringToBooleanConverterTest {
	
	static StringToBooleanConverter converter;
	
	@BeforeAll
	static void setUp() {
		converter = new StringToBooleanConverter();
	}
	
	@Test
	void convert() {
		assertTrue(converter.convert("true"));
		assertTrue(converter.convert("True"));
		assertTrue(converter.convert("TRUE"));
		
		assertFalse(converter.convert("false"));
		assertFalse(converter.convert("False"));
		assertFalse(converter.convert("FALSE"));
	}
	
}