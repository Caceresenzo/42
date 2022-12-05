package ft.framework.orm.predicate;

import java.util.List;

import lombok.Data;
import lombok.RequiredArgsConstructor;

@Data
@RequiredArgsConstructor
public final class Branch<T> implements Predicate<T> {
	
	private final Type type;
	private final List<Predicate<T>> predicates;
	
	public enum Type {
		
		AND,
		OR;
	
	}
	
}