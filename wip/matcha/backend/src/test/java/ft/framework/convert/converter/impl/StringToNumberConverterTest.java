package ft.framework.convert.converter.impl;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class StringToNumberConverterTest {
	
	static StringToNumberConverter converter;
	
	@BeforeAll
	static void setUp() {
		converter = new StringToNumberConverter(Integer::parseInt);
	}
	
	@Test
	void convert() {
		assertEquals(1, converter.convert("1"));
	}
	
}