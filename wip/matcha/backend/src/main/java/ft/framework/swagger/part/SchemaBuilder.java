package ft.framework.swagger.part;

import java.io.InputStream;
import java.lang.reflect.Type;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.UUID;
import java.util.function.Supplier;

import org.apache.commons.lang3.ClassUtils;

import com.fasterxml.jackson.databind.JavaType;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.type.CollectionLikeType;
import com.fasterxml.jackson.databind.type.MapLikeType;
import com.fasterxml.jackson.databind.type.SimpleType;

import io.swagger.v3.oas.models.OpenAPI;
import io.swagger.v3.oas.models.media.ArraySchema;
import io.swagger.v3.oas.models.media.BinarySchema;
import io.swagger.v3.oas.models.media.BooleanSchema;
import io.swagger.v3.oas.models.media.DateSchema;
import io.swagger.v3.oas.models.media.DateTimeSchema;
import io.swagger.v3.oas.models.media.IntegerSchema;
import io.swagger.v3.oas.models.media.ObjectSchema;
import io.swagger.v3.oas.models.media.Schema;
import io.swagger.v3.oas.models.media.StringSchema;
import io.swagger.v3.oas.models.media.UUIDSchema;

public class SchemaBuilder {
	
	public static final ObjectMapper OBJECT_MAPPER = new ObjectMapper();
	public static final Map<Class<?>, Supplier<Schema<?>>> SCHEMA_BUILDERS;
	
	static {
		final var builders = new HashMap<Class<?>, Supplier<Schema<?>>>();
		
		builders.put(Long.class, () -> new IntegerSchema().format("int64"));
		builders.put(Integer.class, IntegerSchema::new);
		builders.put(Boolean.class, BooleanSchema::new);
		builders.put(UUID.class, UUIDSchema::new);
		builders.put(String.class, StringSchema::new);
		builders.put(LocalDate.class, DateSchema::new);
		builders.put(LocalDateTime.class, DateTimeSchema::new);
		builders.put(InputStream.class, BinarySchema::new);
		builders.put(LocalTime.class, () -> new StringSchema().format("time"));
		
		SCHEMA_BUILDERS = Collections.unmodifiableMap(builders);
	}
	
	public static Optional<Schema<?>> build(OpenAPI swagger, Type type) {
		return build(OBJECT_MAPPER.getTypeFactory().constructType(type), swagger);
	}
	
	public static Optional<Schema<?>> build(JavaType type, OpenAPI swagger) {
		if (type.isContainerType()) {
			if (type instanceof CollectionLikeType collectionLikeType) {
				final var schema = new ArraySchema();
				
				build(collectionLikeType.getContentType(), swagger)
					.ifPresent(schema::setItems);
				
				return Optional.of(schema);
			} else if (type instanceof MapLikeType mapLikeType) {
				final var schema = new ObjectSchema();
				
				build(mapLikeType.getContentType(), swagger)
					.ifPresent(schema::setItems);
				
				return Optional.of(schema);
			}
		} else if (type instanceof SimpleType simpleType) {
			final var clazz = ClassUtils.primitiveToWrapper(simpleType.getRawClass());
			
			final var simpleBuilder = SCHEMA_BUILDERS.get(clazz);
			if (simpleBuilder != null) {
				return Optional.of(simpleBuilder.get());
			}
		}
		
		return Optional.of(getOrCreateComponent(swagger, type));
	}
	
	public static Schema<?> getOrCreateComponent(OpenAPI swagger, JavaType type) {
		final var schemas = swagger.getComponents().getSchemas();
		final var name = getName(type);
		
		final var found = schemas.get(name);
		if (found == null) {
			final var schema = new ObjectSchema();
			schema.setName(name);
			
			schemas.put(name, schema);
			
			final var beanDescription = new ObjectMapper().getSerializationConfig().introspect(type);
			final var properties = beanDescription.findProperties();
			
			for (final var property : properties) {
				final var primaryType = property.getPrimaryType();
				
				build(primaryType, swagger)
					.ifPresent((itemSchema) -> schema.addProperty(property.getName(), itemSchema));
			}
		}
		
		return new Schema<>().$ref(name);
	}
	
	public static String getName(JavaType type) {
		final var builder = new StringBuilder();
		
		for (int index = 0; index < type.containedTypeCount(); ++index) {
			final var contained = type.containedType(index);
			
			builder.append(getName(contained));
		}
		
		return builder
			.append(type.getRawClass().getSimpleName())
			.toString();
	}
	
}