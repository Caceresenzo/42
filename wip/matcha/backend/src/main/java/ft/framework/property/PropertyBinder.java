package ft.framework.property;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Optional;
import java.util.Set;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.reflect.FieldUtils;

import ft.framework.convert.service.ConvertionService;
import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.property.resolver.PropertyResolver;
import ft.framework.validation.ValidationException;
import ft.framework.validation.Validator;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.ConstraintViolation;
import lombok.Builder;
import lombok.Getter;
import lombok.Singular;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@Builder
public class PropertyBinder {
	
	private final ConvertionService convertionService;
	private final Validator validator;
	
	@Singular
	@Getter
	private final List<PropertyResolver> resolvers;
	
	public <T> T bind(T instance) {
		final var prefix = extractPrefix(instance.getClass());
		
		return bind(instance, prefix);
	}
	
	@SuppressWarnings("unchecked")
	public <T> T bind(T instance, List<String> prefix) {
		final var clazz = instance.getClass();
		final var fields = FieldUtils.getAllFields(clazz);
		
		for (final var field : fields) {
			final var paths = new ArrayList<String>(prefix);
			paths.add(field.getName());
			
			final var resolved = resolve(paths);
			if (resolved.isPresent()) {
				set(instance, field, resolved.get());
			}
		}
		
		if (clazz.isAnnotationPresent(Valid.class)) {
			final var violations = validator.validate(instance);
			
			if (!violations.isEmpty()) {
				throw new ValidationException((Set<ConstraintViolation<?>>) (Object) violations);
			}
		}
		
		return instance;
	}
	
	@SneakyThrows
	public void set(Object instance, Field field, String value) {
		final var converted = convertionService.convert(value, String.class, field.getType());
		
		FieldUtils.writeField(field, instance, converted, true);
	}
	
	public Optional<String> resolve(List<String> paths) {
		for (final var resolver : resolvers) {
			final var value = resolver.resolve(paths);
			
			if (value.isPresent()) {
				if (log.isDebugEnabled()) {
					final var joined = String.join(".", paths);
					log.trace("Bound {} from {}", joined, resolver.getName());
				}
				
				return value;
			}
		}
		
		return Optional.empty();
	}
	
	public static List<String> extractPrefix(Class<?> clazz) {
		final var annotation = clazz.getAnnotation(ConfigurationProperties.class);
		if (annotation == null) {
			return Collections.emptyList();
		}
		
		final var prefix = annotation.prefix();
		if (StringUtils.isBlank(prefix)) {
			return Collections.emptyList();
		}
		
		return Arrays.asList(prefix.split("\\."));
	}
	
}