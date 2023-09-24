package ft.framework.orm;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
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

import com.mysql.cj.MysqlType;

import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.ddl.DDLStrategy;
import ft.framework.orm.ddl.UpdateDDLStrategy;
import ft.framework.orm.dialect.Dialect;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;
import ft.framework.orm.mapping.MappingBuilder;
import ft.framework.orm.mapping.relationship.ManyToOne;
import ft.framework.orm.predicate.Branch;
import ft.framework.orm.predicate.Comparison;
import ft.framework.orm.predicate.Predicate;
import ft.framework.orm.proxy.EntityHandler;
import ft.framework.orm.proxy.ProxiedEntity;
import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class EntityManager {
	
	@Getter
	private final ConnectionPoolDataSource dataSource;
	private final Dialect dialect;
	private final Map<Class<?>, Entity<?>> entities;
	
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
		final Entity<T> entity = getEntity(instance);
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
			
			log.trace("update: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				T original = instance;
				if (instance instanceof ProxiedEntity proxied) {
					original = (T) proxied.getEntityHandler().getOriginal();
				}
				
				var index = 1;
				for (final var column : columns) {
					var value = column.read(original);
					if (column instanceof ManyToOne manyToOne) {
						final Entity<?> target = manyToOne.getTarget();
						value = target.getTable().getIdColumn().read(value);
					}
					
					statement.setObject(index++, value, MysqlType.VARCHAR /* TODO */);
				}
				
				final var id = table.getIdColumn().read(original);
				statement.setObject(index++, id, MysqlType.VARCHAR /* TODO */);
				
				long affectedRows;
				
				try {
					affectedRows = statement.executeUpdate();
				} catch (SQLIntegrityConstraintViolationException exception) {
					throw dialect.translate(table, exception);
				}
				
				if (instance instanceof ProxiedEntity proxied) {
					proxied.getEntityHandler().reset();
					return new Result<T>(instance, affectedRows, false);
				} else {
					final var converted = convert(entity, instance, false);
					return new Result<T>(converted, affectedRows, false);
				}
			}
		}
	}
	
	@SuppressWarnings("unchecked")
	@SneakyThrows
	public <T> T insert(T instance) {
		final Entity<T> entity = getEntity(instance);
		final var table = entity.getTable();
		final var columns = table.getAllColumnsWithoutId();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildInsertStatement(table, columns);
			
			log.trace("insert: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString(), Statement.RETURN_GENERATED_KEYS)) {
				T original = instance;
				if (instance instanceof ProxiedEntity proxied) {
					original = (T) proxied.getEntityHandler().getOriginal();
				}
				
				var index = 1;
				for (final var column : columns) {
					var value = column.read(original);
					if (column instanceof ManyToOne manyToOne) {
						final Entity<?> target = manyToOne.getTarget();
						value = target.getTable().getIdColumn().read(value);
					}
					
					// System.out.println("binding %s=%s".formatted(index, value));
					statement.setObject(index++, value, MysqlType.VARCHAR /* TODO */);
				}
				
				long affectedRows;
				try {
					affectedRows = statement.executeUpdate();
				} catch (SQLIntegrityConstraintViolationException exception) {
					throw dialect.translate(table, exception);
				}
				
				if (affectedRows == 0) {
					throw new SQLException("Creating failed, no rows affected.");
				}
				
				try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
					if (generatedKeys.next()) {
						final var idColumn = table.getIdColumn();
						final var id = generatedKeys.getObject(1, idColumn.getField().getType());
						idColumn.write(instance, id);
					} else {
						throw new SQLException("Creating failed, no ID obtained.");
					}
				}
			}
		}
		
		return convert(entity, instance, false);
	}
	
	@SneakyThrows
	public <T> boolean delete(T instance) {
		final Entity<T> entity = getEntity(instance);
		final var table = entity.getTable();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildDeleteByIdStatement(table);
			
			log.trace("delete: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				final var id = table.getIdColumn().read(instance);
				
				statement.setObject(1, id, MysqlType.VARCHAR /* TODO */);
				
				return statement.executeUpdate() != 0;
			}
		}
	}
	
	@SneakyThrows
	public <T> long deleteAllBy(Entity<T> entity, Predicate<T> predicate) {
		final var table = entity.getTable();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildDeleteStatement(table, predicate);
			
			log.trace("deleteAllBy: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				applyPredicate(statement, predicate);
				
				return statement.executeLargeUpdate();
			}
		}
	}
	
	@SneakyThrows
	public <T> long countBy(Entity<T> entity, Predicate<T> predicate) {
		final var table = entity.getTable();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildCountStatement(table, predicate);
			
			log.trace("countBy: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				applyPredicate(statement, predicate);
				
				try (ResultSet resultSet = statement.executeQuery()) {
					if (resultSet.next()) {
						return resultSet.getLong(1);
					}
				}
			}
		}
		
		return 0;
	}
	
	@SneakyThrows
	public <T> boolean existsBy(Entity<T> entity, Predicate<T> predicate) {
		final var table = entity.getTable();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildExistsStatement(table, predicate);
			
			log.trace("existsBy: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				applyPredicate(statement, predicate);
				
				try (ResultSet resultSet = statement.executeQuery()) {
					return resultSet.next();
				}
			}
		}
	}
	
	@SneakyThrows
	public <T> Optional<T> findById(Entity<T> entity, Object id) {
		final var table = entity.getTable();
		final var columns = table.getColumns();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildSelectByIdStatement(table, columns);
			
			log.trace("findById: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				statement.setObject(1, id);
				
				try (ResultSet resultSet = statement.executeQuery()) {
					while (resultSet.next()) {
						final T instance = read(entity.instantiate(), resultSet, columns);
						final T converted = convert(entity, instance, false);
						
						if (resultSet.next()) {
							throw new IllegalStateException("more item are available");
						}
						
						return Optional.of(converted);
					}
					
					return Optional.empty();
				}
			}
		}
	}
	
	@SneakyThrows
	public <T> Optional<T> findBy(Entity<T> entity, Predicate<T> predicate) {
		final var table = entity.getTable();
		final var columns = table.getColumns();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildSelectStatement(table, columns, predicate);
			
			log.trace("findBy: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				applyPredicate(statement, predicate);
				
				try (ResultSet resultSet = statement.executeQuery()) {
					while (resultSet.next()) {
						final T instance = read(entity.instantiate(), resultSet, columns);
						final T converted = convert(entity, instance, false);
						
						if (resultSet.next()) {
							throw new IllegalStateException("more item are available");
						}
						
						return Optional.of(converted);
					}
					
					return Optional.empty();
				}
			}
		}
	}
	
	@SneakyThrows
	public <T> List<T> findAllBy(Entity<T> entity, Predicate<T> predicate) {
		final var table = entity.getTable();
		final var columns = table.getColumns();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var sql = dialect.buildSelectStatement(table, columns, predicate, null);
			
			log.trace("findAllBy: {}", sql);
			
			try (final var statement = connection.prepareStatement(sql.toString())) {
				applyPredicate(statement, predicate);
				
				try (ResultSet resultSet = statement.executeQuery()) {
					final var instances = new ArrayList<T>();
					
					while (resultSet.next()) {
						final T instance = read(entity.instantiate(), resultSet, columns);
						final T converted = convert(entity, instance, false);
						
						instances.add(converted);
					}
					
					return instances;
				}
			}
		}
	}
	
	@SneakyThrows
	public <T> Page<T> findAllBy(Entity<T> entity, Predicate<T> predicate, Pageable pageable) {
		final var table = entity.getTable();
		final var columns = table.getColumns();
		
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			final var content = new ArrayList<T>();
			var totalElements = 0l;
			
			{
				final var sql = dialect.buildSelectStatement(table, columns, predicate, pageable);
				
				log.trace("findAllBy: {}", sql);
				
				try (final var statement = connection.prepareStatement(sql.toString())) {
					applyPredicate(statement, predicate);
					
					try (ResultSet resultSet = statement.executeQuery()) {
						while (resultSet.next()) {
							final T instance = read(entity.instantiate(), resultSet, columns);
							final T converted = convert(entity, instance, false);
							
							content.add(converted);
						}
					}
				}
			}
			
			{
				final var sql = dialect.buildCountStatement(table, predicate);
				
				log.trace("findAllBy: {}", sql);
				
				try (final var statement = connection.prepareStatement(sql.toString())) {
					applyPredicate(statement, predicate);
					
					try (ResultSet resultSet = statement.executeQuery()) {
						if (resultSet.next()) {
							totalElements = resultSet.getLong(1);
						}
					}
				}
			}
			
			return new Page<>(content, totalElements, pageable);
		}
	}
	
	@SuppressWarnings({ "unchecked", "rawtypes" })
	@SneakyThrows
	public <T> T read(T instance, ResultSet resultSet, List<Column> columns) {
		int index = 1;
		for (final var column : columns) {
			var value = resultSet.getObject(index++);
			if (column instanceof ManyToOne manyToOne) {
				final Entity target = manyToOne.getTarget();
				
				if (value != null) {
					value = convert(target, target.instantiate(value), true);
				}
			}
			
			column.write(instance, value);
		}
		
		return instance;
	}
	
	@SneakyThrows
	public <T> T convert(Entity<T> entity, T instance, boolean lazy) {
		final var handler = new EntityHandler(this, entity, instance, !lazy);
		final var proxy = entity.getProxyClass()
			.getDeclaredConstructor(EntityHandler.class)
			.newInstance(handler);
		
		final var idColumn = entity.getTable().getIdColumn();
		final var id = idColumn.read(instance);
		idColumn.write(proxy, id);
		
		return proxy;
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
		
		return entity.getTable().getIdColumn().read(instance);
	}
	
	@SuppressWarnings("unchecked")
	public <T> Entity<T> getEntity(Class<T> clazz) {
		final Entity<T> entity = (Entity<T>) entities.get(clazz);
		Objects.requireNonNull(entity, "the instance is not an entity");
		
		return entity;
	}
	
	@SuppressWarnings("unchecked")
	public <T> Entity<T> getEntity(Object instance) {
		Objects.requireNonNull(instance);
		
		if (instance instanceof ProxiedEntity proxied) {
			return (Entity<T>) proxied.getEntityHandler().getEntity();
		}
		
		return (Entity<T>) getEntity(instance.getClass());
	}
	
	public List<Entity<?>> getEntities() {
		return new ArrayList<>(entities.values());
	}
	
	public void applyPredicate(PreparedStatement statement, Predicate<?> predicate) {
		int[] index = { 1 };
		applyPredicate(statement, predicate, index);
	}
	
	@SneakyThrows
	public void applyPredicate(PreparedStatement statement, Predicate<?> predicate, int[] index) {
		if (predicate instanceof Comparison<?> comparison) {
			var value = convertValue(comparison.getValue());
			
			statement.setObject(index[0]++, value, MysqlType.VARCHAR /* TODO */);
		} else if (predicate instanceof Branch<?> branch) {
			for (final Predicate<?> child : branch.getPredicates()) {
				applyPredicate(statement, child, index);
			}
		}
	}
	
	// TODO This should be moved
	public Object convertValue(Object value) {
		if (value instanceof ProxiedEntity proxied) {
			return proxied.getEntityHandler().getId();
		}
		if (value instanceof Enum<?> enum_) {
			return enum_.name();
		}
		
		return value;
	}
	
	@SneakyThrows
	public void applyDataDefinitionLanguage() {
		try (final var connection = dataSource.getPooledConnection().getConnection()) {
			applyDataDefinitionLanguage(new UpdateDDLStrategy(connection, dialect));
		}
	}
	
	@SneakyThrows
	public void applyDataDefinitionLanguage(DDLStrategy strategy) {
		strategy.apply(getEntities());
	}
	
	@Builder
	@Data
	public static class Result<T> {
		
		private final T instance;
		private final long affectedRows;
		private final boolean ignored;
		
	}
	
}