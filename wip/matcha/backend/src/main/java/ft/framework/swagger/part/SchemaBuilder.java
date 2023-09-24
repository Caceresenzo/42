package ft.framework.swagger.part;

import java.io.InputStream;
import java.lang.reflect.Type;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.UUID;
import java.util.function.Supplier;

import javax.servlet.http.Part;

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
import io.swagger.v3.oas.models.media.NumberSchema;
import io.swagger.v3.oas.models.media.ObjectSchema;
import io.swagger.v3.oas.models.media.Schema;
import io.swagger.v3.oas.models.media.StringSchema;
import io.swagger.v3.oas.models.media.UUIDSchema;

public class SchemaBuilder {
	
	public static final ObjectMapper OBJECT_MAPPER = new ObjectMapper();
	public static final Map<Class<?>, Supplier<Schema<?>>> SCHEMA_BUILDERS;
	
	static {
		final var builders = new HashMap<Class<?>, Supplier<Schema<?>>>();
		
		builders.put(long.class, () -> new IntegerSchema().format("int64"));
		builders.put(Long.class, nullable(builders.get(long.class)));
		builders.put(int.class, IntegerSchema::new);
		builders.put(Integer.class, nullable(builders.get(int.class)));
		builders.put(boolean.class, BooleanSchema::new);
		builders.put(Boolean.class, nullable(builders.get(boolean.class)));
		builders.put(float.class, () -> new NumberSchema().format("float"));
		builders.put(Float.class, nullable(builders.get(float.class)));
		builders.put(double.class, () -> new NumberSchema().format("double"));
		builders.put(Double.class, nullable(builders.get(double.class)));
		builders.put(UUID.class, UUIDSchema::new);
		builders.put(String.class, StringSchema::new);
		builders.put(LocalDate.class, DateSchema::new);
		builders.put(LocalDateTime.class, DateTimeSchema::new);
		builders.put(InputStream.class, BinarySchema::new);
		builders.put(LocalTime.class, () -> new StringSchema().format("time"));
		builders.put(Part.class, () -> new BinarySchema());
		
		SCHEMA_BUILDERS = Collections.unmodifiableMap(builders);
	}
	
	public static Supplier<Schema<?>> nullable(Supplier<Schema<?>> supplier) {
		return () -> {
			final var schema = supplier.get();
			schema.setNullable(true);
			
			return schema;
		};
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
			final Class<?> clazz = simpleType.getRawClass();
			
			if (void.class.equals(clazz)) {
				return Optional.empty();
			}
			
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
			final var clazz = type.getRawClass();
			
			if (clazz.isEnum()) {
				final var schema = new StringSchema();
				schema.setName(name);
				
				schemas.put(name, schema);
				
				Arrays.stream(clazz.getEnumConstants())
					.map(Enum.class::cast)
					.map(Enum::name)
					.forEach(schema::addEnumItem);
			} else {
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
		}
		
		return new Schema<>().$ref(name);
	}
	
	public static String getAllEnclosing(Class<?> clazz) {
		final var enclosing = clazz.getEnclosingClass();
		
		if (enclosing == null) {
			return "";
		}
		
		return getAllEnclosing(enclosing) + enclosing.getSimpleName();
	}
	
	public static String getName(JavaType type) {
		final var builder = new StringBuilder();
		
		builder.append(getAllEnclosing(type.getRawClass()));
		
		for (int index = 0; index < type.containedTypeCount(); ++index) {
			final var contained = type.containedType(index);
			
			builder.append(getName(contained));
		}
		
		return builder
			.append(type.getRawClass().getSimpleName())
			.toString();
	}
	
}