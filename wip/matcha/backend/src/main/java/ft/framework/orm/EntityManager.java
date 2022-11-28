package ft.framework.orm;

import java.util.List;

import javax.sql.ConnectionPoolDataSource;

import ft.framework.orm.mapping.Entity;
import ft.framework.orm.mapping.MappingBuilder;
import lombok.Getter;

@Getter
public class EntityManager {
	
	private final ConnectionPoolDataSource dataSource;
	private final List<Entity> entities;
	
	public EntityManager(ConnectionPoolDataSource dataSource, MappingBuilder mappingBuilder) {
		this.dataSource = dataSource;
		this.entities = mappingBuilder.getEntities();
	}
	
	public <T> T persist(T instance) {
		return instance; // TODO
	}
	
	@Deprecated
	public Entity getByClass(Class<?> clazz) {
		for (final var entity : entities) {
			if (entity.getClazz().equals(clazz)) {
				return entity;
			}
		}
		
		return null;
	}
	
}