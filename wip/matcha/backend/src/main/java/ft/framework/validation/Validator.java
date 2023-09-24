package ft.framework.validation;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.Arrays;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

import org.apache.commons.lang3.ClassUtils;
import org.apache.commons.lang3.reflect.FieldUtils;

import ft.framework.validation.constraint.ConstraintDescriptor;
import ft.framework.validation.constraint.ConstraintValidator;
import ft.framework.validation.constraint.ConstraintViolation;
import lombok.SneakyThrows;

public class Validator {
	
	public <T> Set<ConstraintViolation<T>> validate(T object) {
		return Arrays.stream(FieldUtils.getAllFields(object.getClass()))
			.map((field) -> validate(object, field))
			.flatMap(Set::stream)
			.collect(Collectors.toSet());
	}
	
	@SuppressWarnings("unchecked")
	public <T> T validateOrThrow(T object) {
		final var violations = validate(object);
		
		if (!violations.isEmpty()) {
			throw new ValidationException((Set<ConstraintViolation<?>>) (Object) violations);
		}
		
		return object;
	}
	
	@SneakyThrows
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public <T> Set<ConstraintViolation<T>> validate(T object, Field field) {
		final var violations = new LinkedHashSet<ConstraintViolation<T>>();
		
		final var value = FieldUtils.readField(field, object, true);
		
		for (final var descriptor : getConstraintDescriptors(field)) {
			final var annotation = descriptor.getAnnotation();
			
			ConstraintValidator validator = getConstraintValidator(field, descriptor);
			if (validator == null) {
				continue;
			}
			
			validator.initialize(annotation);
			
			if (!validator.isValid(value)) {
				// TODO Support sub-object
				final var path = field.getName();
				
				violations.add(new ConstraintViolation<>(descriptor.getMessage(), path, value));
			}
		}
		
		return violations;
	}
	
	public List<ConstraintDescriptor<Annotation>> getConstraintDescriptors(Field field) {
		return Arrays.stream(field.getAnnotations())
			.map(ConstraintDescriptor::from)
			.filter(Optional::isPresent)
			.map(Optional::get)
			.toList();
	}
	
	@SneakyThrows
	public ConstraintValidator<?, ?> getConstraintValidator(Field field, ConstraintDescriptor<?> descritor) {
		for (final var validatorClass : descritor.getConstraintValidatorClasses()) {
			final var type = extractConstraintValidatorType(validatorClass);
			
			if (type instanceof Class<?> clazz && ClassUtils.isAssignable(field.getType(), clazz, true)) {
				// TODO Get from context
				return validatorClass.getConstructor().newInstance();
			}
		}
		
		return null;
	}
	
	public Type extractConstraintValidatorType(Class<? extends ConstraintValidator<?, ?>> validatorClass) {
		for (final var interface_ : validatorClass.getGenericInterfaces()) {
			if (interface_ instanceof ParameterizedType type) {
				if (ConstraintValidator.class.equals(type.getRawType())) {
					return type.getActualTypeArguments()[1];
				}
			}
		}
		
		// TODO Support super generics
		// final var super_ = validatorClass.getSuperclass();
		// if (super_.isAssignableFrom(ConstraintValidator.class)) {
		// return extractConstraintValidatorType((Class<? extends ConstraintValidator<?, ?>>) super_);
		// }
		
		return null;
	}
	
}