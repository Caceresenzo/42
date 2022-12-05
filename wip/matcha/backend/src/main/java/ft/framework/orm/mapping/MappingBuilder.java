package ft.framework.orm.mapping;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Objects;

import javax.persistence.Lob;
import javax.persistence.UniqueConstraint;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.reflect.FieldUtils;

import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.naming.LowerCaseNamingStrategy;
import ft.framework.orm.mapping.naming.NamingStrategy;
import ft.framework.orm.mapping.naming.PluralNamingStrategy;
import ft.framework.orm.mapping.relationship.ManyToOne;
import ft.framework.orm.proxy.EntityHandler;
import ft.framework.orm.proxy.EntityHandlerInterceptor;
import ft.framework.orm.proxy.ProxiedEntity;
import lombok.SneakyThrows;
import net.bytebuddy.ByteBuddy;
import net.bytebuddy.description.modifier.Visibility;
import net.bytebuddy.dynamic.loading.ClassLoadingStrategy;
import net.bytebuddy.dynamic.scaffold.subclass.ConstructorStrategy;
import net.bytebuddy.implementation.FieldAccessor;
import net.bytebuddy.implementation.MethodCall;
import net.bytebuddy.implementation.MethodDelegation;
import net.bytebuddy.matcher.ElementMatchers;

public class MappingBuilder {
	
	private NamingStrategy tableNamingStrategy = new PluralNamingStrategy(LowerCaseNamingStrategy.INSTANCE);
	private NamingStrategy columnNamingStrategy = LowerCaseNamingStrategy.INSTANCE;
	private List<Entity<?>> entities = new ArrayList<>();
	
	public <T> Entity<T> analyze(Class<T> clazz) {
		var entity = getByClass(clazz);
		if (entity != null) {
			return entity;
		}
		
		entity = buildEntity(clazz);
		entities.add(entity);
		
		return entity;
	}
	
	public <T> Entity<T> buildEntity(Class<T> clazz) {
		final var annotation = clazz.getAnnotation(javax.persistence.Entity.class);
		if (annotation == null) {
			return null;
		}
		
		var name = annotation.name();
		if (StringUtils.isEmpty(name)) {
			name = clazz.getSimpleName();
		}
		
		return Entity.<T>builder()
			.name(name)
			.clazz(clazz)
			.proxyClass(createProxyClass(clazz))
			.table(buildTable(clazz, name))
			.build();
	}
	
	@SneakyThrows
	public <T> Class<? extends T> createProxyClass(Class<T> clazz) {
		return new ByteBuddy()
			.subclass(clazz, ConstructorStrategy.Default.NO_CONSTRUCTORS)
			.defineConstructor(Visibility.PUBLIC)
			.withParameter(EntityHandler.class)
			.intercept(MethodCall.invoke(clazz.getDeclaredConstructor())
				.andThen(FieldAccessor.ofField(ProxiedEntity.HANDLER_FIELD).setsArgumentAt(0)))
			.defineField(ProxiedEntity.HANDLER_FIELD, EntityHandler.class, Visibility.PUBLIC)
			.implement(ProxiedEntity.class)
			.intercept(FieldAccessor.ofField(ProxiedEntity.HANDLER_FIELD))
			.method(ElementMatchers.isDeclaredBy(clazz))
			.intercept(MethodDelegation.to(EntityHandlerInterceptor.class))
			.make()
			.load(clazz.getClassLoader(), ClassLoadingStrategy.Default.WRAPPER)
			.getLoaded();
	}
	
	public String getTableName(javax.persistence.Table annotation, String entityName) {
		if (annotation != null) {
			return tableNamingStrategy.convertNameIfEmpty(annotation.name(), entityName);
		}
		
		return tableNamingStrategy.convertName(entityName);
	}
	
	@SuppressWarnings("unchecked")
	public Table buildTable(Class<?> clazz, String entityName) {
		final var annotation = clazz.getAnnotation(javax.persistence.Table.class);
		final var name = getTableName(annotation, entityName);
		
		final var columns = new ArrayList<Column>();
		
		final var table = Table.builder()
			.name(name);
		
		var idSet = false;
		
		for (final var field : FieldUtils.getAllFields(clazz)) {
			final var idAnnotation = field.getAnnotation(javax.persistence.Id.class);
			final var columnAnnotation = field.getAnnotation(javax.persistence.Column.class);
			final var manyToOneAnnotation = field.getAnnotation(javax.persistence.ManyToOne.class);
			
			if (idAnnotation == null && columnAnnotation == null && manyToOneAnnotation == null) {
				continue;
			}
			
			var columnName = "";
			if (columnAnnotation != null) {
				columnName = columnAnnotation.name();
			}
			
			if (manyToOneAnnotation != null) {
				if (idAnnotation != null) {
					throw new IllegalStateException("many to one cannot be the table id");
				}
				
				final var manyToOne = ManyToOne.builder()
					.field(field)
					.name(columnNamingStrategy.convertIdNameIfEmpty(columnName, field.getName()));
				
				if (manyToOneAnnotation != null) {
					manyToOne.nullable(manyToOneAnnotation.optional());
				}
				
				var targetEntityClass = manyToOneAnnotation.targetEntity();
				if (targetEntityClass == void.class) {
					targetEntityClass = field.getType();
				}
				
				final var targetEntity = analyze(targetEntityClass);
				Objects.requireNonNull(targetEntity, targetEntityClass.getSimpleName() + " is not an entity");
				
				manyToOne
					.target(targetEntity)
					.dataType(targetEntity.getTable().getIdColumn().getDataType());
				
				table.manyToOne(manyToOne.build());
			} else {
				final var dataTypeBuilder = DataType.builder()
					.type(field.getType())
					.lotOfByte(field.isAnnotationPresent(Lob.class));
				
				if (columnAnnotation != null) {
					final var precision = columnAnnotation.precision();
					if (precision != 0) {
						dataTypeBuilder.precision(precision);
					}
					
					final var scale = columnAnnotation.scale();
					if (scale != 0) {
						dataTypeBuilder.precision(scale);
					}
					
					final var length = columnAnnotation.length();
					if (length != 0) {
						dataTypeBuilder.precision(length);
					}
				}
				
				final var dataType = dataTypeBuilder.build();
				
				columnName = columnNamingStrategy.convertNameIfEmpty(columnName, field.getName());
				
				final var columnBuilder = Column.builder()
					.field(field)
					.name(columnName)
					.dataType(dataType);
				
				if (columnAnnotation != null) {
					columnBuilder.nullable(columnAnnotation.nullable());
				}
				
				if (idAnnotation != null) {
					columnBuilder.nullable(false);
				}
				
				final var column = columnBuilder.build();
				columns.add(column);
				
				if (columnAnnotation != null && columnAnnotation.unique()) {
					table.unique(Unique.builder()
						.name("")
						.column(column)
						.build());
				}
				
				if (idAnnotation != null) {
					if (idSet) {
						throw new IllegalArgumentException("multiple id found");
					}
					
					idSet = true;
					table.idColumn(column);
				}
			}
		}
		
		for (final var indexAnnotation : annotation.indexes()) {
			table.index(buildIndex(indexAnnotation, columns));
		}
		
		for (final var uniqueAnnotation : annotation.uniqueConstraints()) {
			table.unique(buildUnique(uniqueAnnotation, columns));
		}
		
		if (!idSet) {
			throw new IllegalArgumentException("no id found");
		}
		
		return table
			.columns(columns)
			.build();
	}
	
	private Index buildIndex(javax.persistence.Index annotation, List<Column> columns) {
		final var filteredColumns = getColumnsByNames(columns, annotation.columnList().split(","));
		if (filteredColumns.isEmpty()) {
			throw new IllegalArgumentException("@Index must have at least one column");
		}
		
		return Index.builder()
			.name(annotation.name())
			.columns(columns)
			.unique(annotation.unique())
			.build();
	}
	
	private Unique buildUnique(UniqueConstraint annotation, List<Column> columns) {
		final var filteredColumns = getColumnsByNames(columns, annotation.columnNames());
		if (filteredColumns.isEmpty()) {
			throw new IllegalArgumentException("@UniqueConstraint must have at least one column");
		}
		
		return Unique.builder()
			.name(annotation.name())
			.columns(columns)
			.build();
	}
	
	public List<Column> getColumnsByNames(List<Column> columns, String[] names) {
		return Arrays.stream(names)
			.map((column) -> getColumnByName(columns, column))
			.toList();
	}
	
	public Column getColumnByName(List<Column> columns, String name) {
		for (final var column : columns) {
			if (column.getField().getName().equals(name)) {
				return column;
			}
		}
		
		throw new NoSuchElementException("no column with name: " + name);
	}
	
	@SuppressWarnings("unchecked")
	public <T> Entity<T> getByClass(Class<T> clazz) {
		for (final var entity : entities) {
			if (entity.getClazz().equals(clazz)) {
				return (Entity<T>) entity;
			}
		}
		
		return null;
	}
	
	public List<Entity<?>> getEntities() {
		return new ArrayList<>(entities);
	}
	
}