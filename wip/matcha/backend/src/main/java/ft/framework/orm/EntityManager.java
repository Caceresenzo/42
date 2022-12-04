package ft.framework.orm;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Collectors;

import javax.sql.ConnectionPoolDataSource;

import org.apache.commons.lang3.reflect.FieldUtils;

import com.mysql.cj.MysqlType;

import ft.framework.orm.dialect.Dialect;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;
import ft.framework.orm.mapping.MappingBuilder;
import ft.framework.orm.mapping.relationship.ManyToOne;
import ft.framework.orm.proxy.EntityHandler;
import ft.framework.orm.proxy.ProxiedEntity;
import lombok.Builder;
import lombok.Data;
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
			return update(instance).getInstance();
		}
	}
	
	@SuppressWarnings("unchecked")
	@SneakyThrows
	public <T> Result<T> update(T instance) {
		final var entity = getEntity(instance);
		final var table = entity.getTable();
		
		Collection<Column> columns;
		if (instance instanceof ProxiedEntity proxied) {
			columns = proxied.getEntityHandler().getModifiedColumns();
			
			if (columns.isEmpty()) {
				return new Result<T>(instance, 0, true);
			}
		} else {
			columns = table.getAllColumnsWithoutId();
		}
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildUpdateByIdStatement(table, columns);
			
			System.out.println(sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				T original = instance;
				if (instance instanceof ProxiedEntity proxied) {
					original = (T) proxied.getEntityHandler().getOriginal();
				}
				
				var index = 1;
				for (final var column : columns) {
					var value = FieldUtils.readField(column.getField(), original, true);
					if (column instanceof ManyToOne manyToOne) {
						final Entity target = manyToOne.getTarget();
						value = target.getTable().getIdColumn().read(value);
					}
					
					statement.setObject(index++, value, MysqlType.VARCHAR /* TODO */);
				}
				
				final var id = table.getIdColumn().read(original);
				statement.setObject(index++, id, MysqlType.VARCHAR /* TODO */);
				
				final var affectedRows = statement.executeUpdate();
				
				if (instance instanceof ProxiedEntity proxied) {
					proxied.getEntityHandler().reset();
					return new Result<T>(instance, affectedRows, false);
				} else {
					final var converted = convert(entity, instance);
					return new Result<T>(converted, affectedRows, false);
				}
			}
		}
	}
	
	@SneakyThrows
	public <T> T insert(T instance) {
		final var entity = getEntity(instance);
		final var table = entity.getTable();
		final var columns = table.getAllColumnsWithoutId();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildInsertStatement(table, columns);
			
			try (final var statement = connection.prepareStatement(sql.toString(), Statement.RETURN_GENERATED_KEYS)) {
				var index = 1;
				for (final var column : columns) {
					var value = FieldUtils.readField(column.getField(), instance, true);
					if (column instanceof ManyToOne manyToOne) {
						final Entity target = manyToOne.getTarget();
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
		
		return convert(entity, instance);
	}
	
	@SuppressWarnings("unchecked")
	@SneakyThrows
	public <T> Optional<T> find(Class<T> clazz, Object id) {
		final var entity = getEntity(clazz);
		final var table = entity.getTable();
		final var columns = table.getAllColumnsWithoutId();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildSelectByIdStatement(table, columns);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				statement.setObject(1, id, MysqlType.VARCHAR /* TODO */);
				
				try (ResultSet resultSet = statement.executeQuery()) {
					while (resultSet.next()) {
						final T instance = read((T) entity.instantiate(id), resultSet, columns);
						final T converted = convert(entity, instance);
						
						return Optional.of(converted);
					}
					
					return Optional.empty();
				}
			}
		}
	}
	
	@SuppressWarnings("unchecked")
	@SneakyThrows
	public <T> List<T> findAll(Class<T> clazz) {
		final var entity = getEntity(clazz);
		final var table = entity.getTable();
		final var columns = table.getAllColumns();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildSelectStatement(table, columns);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				try (ResultSet resultSet = statement.executeQuery()) {
					final var instances = new ArrayList<T>();
					
					while (resultSet.next()) {
						final T instance = read((T) entity.instantiate(), resultSet, columns);
						final T converted = convert(entity, instance);
						
						instances.add(converted);
					}
					
					return instances;
				}
			}
		}
	}
	
	@SneakyThrows
	public <T> T read(T instance, ResultSet resultSet, List<Column> columns) {
		int index = 1;
		for (final var column : columns) {
			var value = resultSet.getObject(index++);
			if (column instanceof ManyToOne manyToOne) {
				final Entity target = manyToOne.getTarget();
				
				// TODO Use proxy
				value = target.instantiate(value);
			}
			
			column.write(instance, value);
		}
		
		return instance;
	}
	
	@SneakyThrows
	public <T> T convert(Entity entity, T instance) {
		final var handler = new EntityHandler(entity, instance);
		final var proxy = entity.getProxyClass()
			.getDeclaredConstructor(EntityHandler.class)
			.newInstance(handler);
		
		return (T) proxy;
	}
	
	@SneakyThrows
	public boolean isNew(Object instance) {
		if (instance instanceof ProxiedEntity) {
			return false;
		}
		
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
	
	public Entity getEntity(Class<?> clazz) {
		final var entity = entities.get(clazz);
		Objects.requireNonNull(entity, "the instance is not an entity");
		
		return entity;
	}
	
	public Entity getEntity(Object instance) {
		Objects.requireNonNull(instance);
		
		if (instance instanceof ProxiedEntity proxied) {
			return proxied.getEntityHandler().getEntity();
		}
		
		return getEntity(instance.getClass());
	}
	
	public List<Entity> getEntities() {
		return new ArrayList<>(entities.values());
	}
	
	@Builder
	@Data
	public static class Result<T> {
		
		private final T instance;
		private final long affectedRows;
		private final boolean ignored;
		
	}
	
}