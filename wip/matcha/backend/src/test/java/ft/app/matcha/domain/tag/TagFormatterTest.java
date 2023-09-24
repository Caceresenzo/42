package ft.app.matcha.domain.tag;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

class TagFormatterTest {
	
	@Test
	void format() {
		assertEquals("aa", TagFormatter.format("AA"));
		assertEquals("a-a", TagFormatter.format("A  A"));
		assertEquals("a-a", TagFormatter.format("A  A"));
		assertEquals("a-a", TagFormatter.format("A_ A"));
		assertEquals("a-a", TagFormatter.format("A--A"));
	}
	
}