package ft.framework.orm.predicate;

import java.util.Arrays;
import java.util.List;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;

public class PredicateBuilder<T> {
	
	private final Entity<T> entity;
	
	public PredicateBuilder(Entity<T> entity) {
		this.entity = entity;
	}
	
	@SafeVarargs
	public final Branch<T> and(Predicate<T>... predicates) {
		return and(Arrays.asList(predicates));
	}
	
	public Branch<T> and(List<Predicate<T>> predicates) {
		return branch(Branch.Type.AND, predicates);
	}

	@SafeVarargs
	public final Branch<T> or(Predicate<T>... predicates) {
		return or(Arrays.asList(predicates));
	}
	
	public Branch<T> or(List<Predicate<T>> predicates) {
		return branch(Branch.Type.OR, predicates);
	}
	
	public Comparison<T> equals(String property, Object value) {
		return compare(Comparison.Type.EQUALS, property, value);
	}
	
	public Comparison<T> equals(Column column, Object value) {
		return compare(Comparison.Type.EQUALS, column, value);
	}
	
	public Comparison<T> notEquals(String property, Object value) {
		return compare(Comparison.Type.NOT_EQUALS, property, value);
	}
	
	public Comparison<T> isNull(String property) {
		return compare(Comparison.Type.IS, property, null);
	}
	
	public Comparison<T> isNotNull(String property) {
		return compare(Comparison.Type.IS_NOT, property, null);
	}
	
	public Comparison<T> lessThan(String property, Object value) {
		return compare(Comparison.Type.LESS_THAN, property, value);
	}
	
	public Comparison<T> lessThanEquals(String property, Object value) {
		return compare(Comparison.Type.LESS_THAN_EQUALS, property, value);
	}
	
	public Comparison<T> greaterThan(String property, Object value) {
		return compare(Comparison.Type.GREATER_THAN, property, value);
	}
	
	public Comparison<T> greaterThanEquals(String property, Object value) {
		return compare(Comparison.Type.GREATER_THAN_EQUALS, property, value);
	}
	
	public Branch<T> branch(Branch.Type type, List<Predicate<T>> predicates) {
		return new Branch<>(type, predicates);
	}
	
	public Comparison<T> compare(Comparison.Type type, String property, Object value) {
		final var column = entity.getTable().getColumnByFieldName(property);
		
		return compare(type, column, value);
	}
	
	public Comparison<T> compare(Comparison.Type type, Column column, Object value) {
		return new Comparison<>(type, column, value);
	}
	
}