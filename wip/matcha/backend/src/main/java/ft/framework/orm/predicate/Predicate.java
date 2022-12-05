package ft.framework.orm.predicate;

public sealed interface Predicate<T> permits Comparison<T>, Branch<T> {
	
}