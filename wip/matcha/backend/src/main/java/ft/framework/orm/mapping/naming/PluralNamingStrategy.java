package ft.framework.orm.mapping.naming;

import org.atteo.evo.inflector.English;

import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class PluralNamingStrategy implements NamingStrategy {
	
	private final NamingStrategy delegate;
	
	@Override
	public String convertName(String camelCase) {
		final var plural = English.plural(camelCase);
		
		return delegate.convertName(plural);
	}
	
}