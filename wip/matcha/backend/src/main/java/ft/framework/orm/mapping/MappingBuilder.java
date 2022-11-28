package ft.framework.orm.mapping;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import javax.persistence.Lob;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.reflect.FieldUtils;

import ft.framework.orm.mapping.naming.LowerCaseNamingStrategy;
import ft.framework.orm.mapping.naming.NamingStrategy;
import ft.framework.orm.mapping.naming.PluralNamingStrategy;
import ft.framework.orm.mapping.relationship.ManyToOne;

public class MappingBuilder {
	
	private NamingStrategy tableNamingStrategy = new PluralNamingStrategy(LowerCaseNamingStrategy.INSTANCE);
	private NamingStrategy columnNamingStrategy = LowerCaseNamingStrategy.INSTANCE;
	private List<Entity> entities = new ArrayList<>();
	
	public Entity analyze(Class<?> clazz) {
		var entity = getByClass(clazz);
		if (entity != null) {
			return entity;
		}
		
		entity = buildEntity(clazz);
		entities.add(entity);
		
		return entity;
	}
	
	public Entity buildEntity(Class<?> clazz) {
		final var annotation = clazz.getAnnotation(javax.persistence.Entity.class);
		if (annotation == null) {
			return null;
		}
		
		var name = annotation.name();
		if (StringUtils.isEmpty(name)) {
			name = clazz.getSimpleName();
		}
		
		return Entity.builder()
			.name(name)
			.clazz(clazz)
			.table(buildTable(clazz, name))
			.build();
	}
	
	public String getTableName(javax.persistence.Table annotation, String entityName) {
		if (annotation != null) {
			return tableNamingStrategy.convertNameIfEmpty(annotation.name(), entityName);
		}
		
		return tableNamingStrategy.convertName(entityName);
	}
	
	public Table buildTable(Class<?> clazz, String entityName) {
		final var annotation = clazz.getAnnotation(javax.persistence.Table.class);
		final var name = getTableName(annotation, entityName);
		
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
				table.column(column);
				
				if (idAnnotation != null) {
					if (idSet) {
						throw new IllegalArgumentException("multiple id found");
					}
					
					idSet = true;
					table.idColumn(column);
				}
			}
		}
		
		if (!idSet) {
			throw new IllegalArgumentException("no id found");
		}
		
		return table.build();
	}
	
	public Entity getByClass(Class<?> clazz) {
		for (final var entity : entities) {
			if (entity.getClazz().equals(clazz)) {
				return entity;
			}
		}
		
		return null;
	}
	
	public List<Entity> getEntities() {
		return new ArrayList<>(entities);
	}
	
}