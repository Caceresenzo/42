package ft.framework.orm.proxy;

import java.util.HashSet;
import java.util.Set;

import ft.framework.orm.EntityManager;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;
import lombok.Data;

@Data
public class EntityHandler {
	
	private final EntityManager entityManager;
	private final Entity<?> entity;
	private final Set<Column> modifiedColumns;
	private Object original;
	private boolean initialized;
	
	public EntityHandler(EntityManager entityManager, Entity<?> entity, Object original, boolean initialized) {
		this.entityManager = entityManager;
		this.entity = entity;
		this.modifiedColumns = new HashSet<>(entity.getTable().getColumnCount());
		this.original = original;
		this.initialized = initialized;
	}
	
	public Object getId() {
		return entity.getTable().getIdColumn().read(original);
	}
	
	public void reset() {
		this.modifiedColumns.clear();
	}
	
	public Object getOriginal() {
		return original;
	}
	
	public boolean isMatchingIdColumn(String name) {
		final var table = entity.getTable();
		
		return table.getIdColumn().isMatching(name);
	}
	
	public boolean markModified(String name) {
		if (isMatchingIdColumn(name)) {
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
	
	public synchronized void fetchLazy() {
		if (!initialized) {
			final var id = entity.getTable().getIdColumn().read(original);
			final var instance = (ProxiedEntity) entityManager.findById(entity, id)
				.orElseThrow(() -> new IllegalStateException("no %s with id %s".formatted(entity.getName(), id)));
			
			// TODO Have the Entity Manager directly give the original
			original = instance.getEntityHandler().getOriginal();
			
			initialized = true;
		}
	}
	
}