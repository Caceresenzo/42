package ft.framework.orm.proxy;

import java.util.HashSet;
import java.util.Set;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;
import lombok.Data;

@Data
public class EntityHandler {
	
	private final Entity<?> entity;
	private final Object original;
	private final Set<Column> modifiedColumns;
	
	public EntityHandler(Entity<?> entity, Object original) {
		this.entity = entity;
		this.original = original;
		this.modifiedColumns = new HashSet<>(entity.getTable().getColumnCount());
	}
	
	public void reset() {
		this.modifiedColumns.clear();
	}
	
	public boolean markModified(String name) {
		final var table = entity.getTable();
		
		if (table.getIdColumn().isMatching(name)) {
			throw new IllegalStateException("ID cannot be modified");
		}
		
		final var column = entity.getTable().getAllColumnsWithoutId()
			.stream()
			.filter((column_) -> column_.isMatching(name))
			.findFirst();
		
		if (column.isEmpty()) {
			return false;
		}
		
		modifiedColumns.add(column.get());
		return true;
	}
	
	public void markAllModified() {
		modifiedColumns.addAll(entity.getTable().getAllColumnsWithoutId());
	}
	
}