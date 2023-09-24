package ft.framework.orm.predicate;

// TODO Eclipse bug: https://stackoverflow.com/a/69492633/7292958
@SuppressWarnings("rawtypes")
public sealed interface Predicate<T> permits Comparison, Branch {
}