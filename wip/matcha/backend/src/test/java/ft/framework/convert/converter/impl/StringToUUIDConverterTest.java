package ft.framework.convert.converter.impl;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.UUID;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class StringToUUIDConverterTest {
	
	static StringToUUIDConverter converter;
	
	@BeforeAll
	static void setUp() {
		converter = new StringToUUIDConverter();
	}
	
	@Test
	void convert() {
		final var uuid = UUID.randomUUID();
		
		assertEquals(uuid, converter.convert(uuid.toString()));
	}
	
}