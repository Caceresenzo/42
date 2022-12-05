package ft.framework.orm.predicate;

import ft.framework.orm.mapping.Column;
import lombok.Data;
import lombok.RequiredArgsConstructor;

@Data
@RequiredArgsConstructor
public final class Comparison<T> implements Predicate<T> {
	
	private final Type type;
	private final Column column;
	private final Object value;
	
	public enum Type {
		
		EQUALS,
		NOT_EQUALS,
		IS,
		IS_NOT,
		LESS_THAN,
		LESS_THAN_EQUALS,
		GREATER_THAN,
		GREATER_THAN_EQUALS,
		// TODO Add more
		;
		
	}
	
}