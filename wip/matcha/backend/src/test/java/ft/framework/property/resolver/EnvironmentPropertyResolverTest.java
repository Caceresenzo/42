package ft.framework.property.resolver;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.Arrays;
import java.util.Optional;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

class EnvironmentPropertyResolverTest {
	
	static EnvironmentPropertyResolver resolver;
	
	@BeforeAll
	static void setUp() {
		resolver = new EnvironmentPropertyResolver();
	}
	
	@Test
	void resolve() {
		System.setProperty("A", "hello");
		
		assertEquals(Optional.of("hello"), resolver.resolve(Arrays.asList("A")));
		assertEquals(Optional.empty(), resolver.resolve(Arrays.asList("B")));
	}
	
	@Test
	void toKey() {
		assertEquals("A", EnvironmentPropertyResolver.toKey(Arrays.asList("a")));
		assertEquals("A_B", EnvironmentPropertyResolver.toKey(Arrays.asList("a", "b")));
		assertEquals("A_B_C", EnvironmentPropertyResolver.toKey(Arrays.asList("a", "b", "c")));
		
		assertEquals("HELLO_WORLD", EnvironmentPropertyResolver.toKey(Arrays.asList("helloWorld")));
		assertEquals("HELLO_WORLD_FROM_ENV_VAR", EnvironmentPropertyResolver.toKey(Arrays.asList("helloWorld", "from", "envVar")));
	}
	
}