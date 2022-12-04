package ft.framework.swagger.part;

import java.io.InputStream;
import java.lang.reflect.AnnotatedElement;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.UUID;
import java.util.function.Supplier;

import org.apache.commons.lang3.ClassUtils;
import org.apache.commons.lang3.reflect.FieldUtils;

import com.fasterxml.jackson.annotation.JsonIgnore;

import io.swagger.models.properties.ArrayProperty;
import io.swagger.models.properties.BinaryProperty;
import io.swagger.models.properties.BooleanProperty;
import io.swagger.models.properties.DateProperty;
import io.swagger.models.properties.DateTimeProperty;
import io.swagger.models.properties.IntegerProperty;
import io.swagger.models.properties.LongProperty;
import io.swagger.models.properties.ObjectProperty;
import io.swagger.models.properties.Property;
import io.swagger.models.properties.StringProperty;
import io.swagger.models.properties.UUIDProperty;

public class PropertyBuilder {
	
	public static final Map<Class<?>, Supplier<Property>> propertyBuilders;
	
	static {
		final var builders = new HashMap<Class<?>, Supplier<Property>>();
		
		builders.put(Long.class, LongProperty::new);
		builders.put(Integer.class, IntegerProperty::new);
		builders.put(Boolean.class, BooleanProperty::new);
		builders.put(UUID.class, UUIDProperty::new);
		builders.put(String.class, StringProperty::new);
		builders.put(LocalDate.class, DateProperty::new);
		builders.put(LocalDateTime.class, DateTimeProperty::new);
		builders.put(InputStream.class, BinaryProperty::new);
		builders.put(LocalTime.class, () -> {
			final var property = new StringProperty();
			property.setFormat("time");
			
			return property;
		});
		
		propertyBuilders = Collections.unmodifiableMap(builders);
	}
	
	public static Optional<Property> build(Type type) {
		if (type instanceof ParameterizedType parameterizedType) {
			final var raw = parameterizedType.getRawType();
			
			if (List.class.equals(raw)) {
				final var property = new ArrayProperty();
				build(parameterizedType.getActualTypeArguments()[0])
					.ifPresent(property::setItems);
				
				return Optional.of(property);
			}
		}
		
		if (type instanceof Class<?> clazz) {
			clazz = ClassUtils.primitiveToWrapper(clazz);
			
			final var simpleBuilder = propertyBuilders.get(clazz);
			if (simpleBuilder != null) {
				return Optional.of(simpleBuilder.get());
			}
			
			final var property = new ObjectProperty();
			for (final var field : FieldUtils.getAllFields(clazz)) {
				build(field, field.getName(), field.getGenericType())
					.ifPresent((property_) -> property.property(field.getName(), property_));
			}
			
			return Optional.of(property);
		}
		
		throw new RuntimeException("cannot convert to property: " + type);
	}
	
	public static Optional<Property> build(AnnotatedElement annotatedElement, String name, Type type) {
		if (annotatedElement.isAnnotationPresent(JsonIgnore.class)) {
			return Optional.empty();
		}
		
		return build(type)
			.map((property) -> {
				property.setName(name);
				return property;
			});
	}
	
}