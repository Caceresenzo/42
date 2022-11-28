package ft.framework.orm;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.function.Function;
import java.util.stream.Collectors;

import javax.sql.ConnectionPoolDataSource;

import org.apache.commons.lang3.reflect.FieldUtils;

import com.mysql.cj.MysqlType;

import ft.framework.orm.dialect.Dialect;
import ft.framework.orm.mapping.Entity;
import ft.framework.orm.mapping.MappingBuilder;
import ft.framework.orm.mapping.relationship.Relationship;
import lombok.Getter;
import lombok.SneakyThrows;

public class EntityManager {
	
	@Getter
	private final ConnectionPoolDataSource dataSource;
	private final Dialect dialect;
	private final Map<Class<?>, Entity> entities;
	
	public EntityManager(ConnectionPoolDataSource dataSource, Dialect dialect, MappingBuilder mappingBuilder) {
		this.dataSource = dataSource;
		this.dialect = dialect;
		this.entities = mappingBuilder.getEntities().stream().collect(Collectors.toMap(Entity::getClazz, Function.identity()));
	}
	
	public <T> T persist(T instance) {
		if (isNew(instance)) {
			return insert(instance);
		} else {
			return update(instance);
		}
	}
	
	public <T> T update(T instance) {
		return instance; // TODO
	}
	
	@SneakyThrows
	public <T> T insert(T instance) {
		final var entity = getEntity(instance);
		final var table = entity.getTable();
		final var columns = table.getAllColumnsWithoutId();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildInsertStatement(table, columns);
			
			System.out.println(sql.toString());
			try (final var statement = connection.prepareStatement(sql.toString(), Statement.RETURN_GENERATED_KEYS)) {
				var index = 1;
				for (final var column : columns) {
					var value = FieldUtils.readField(column.getField(), instance, true);
					if (column instanceof Relationship relationship) {
						final Entity target = relationship.getTarget();
						value = target.getTable().getIdColumn().read(value);
					}
					
					statement.setObject(index++, value, MysqlType.VARCHAR /* TODO */);
				}
				
				final var affectedRows = statement.executeUpdate();
				if (affectedRows == 0) {
					throw new SQLException("Creating failed, no rows affected.");
				}
				
				try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
					if (generatedKeys.next()) {
						final var idField = table.getIdColumn().getField();
						final var id = generatedKeys.getObject(1, idField.getType());
						FieldUtils.writeField(idField, instance, id, true);
					} else {
						throw new SQLException("Creating failed, no ID obtained.");
					}
				}
			}
		}
		
		return instance;
	}
	
	@SneakyThrows
	public boolean isNew(Object instance) {
		final var id = getId(instance);
		
		if (id == null) {
			return true;
		} else if (Long.class.equals(id.getClass())) {
			return Objects.equals(0L, id);
		} else if (int.class.equals(id.getClass())) {
			return Objects.equals(0, id);
		} else {
			return false;
		}
	}
	
	@SneakyThrows
	public Object getId(Object instance) {
		final var entity = getEntity(instance);
		
		return FieldUtils.readField(entity.getTable().getIdColumn().getField(), instance, true);
	}
	
	public Entity getEntity(Object instance) {
		Objects.requireNonNull(instance);
		
		final var entity = entities.get(instance.getClass());
		Objects.requireNonNull(entity, "the instance is not an entity");
		
		return entity;
	}
	
	public List<Entity> getEntities() {
		return new ArrayList<>(entities.values());
	}
	
}