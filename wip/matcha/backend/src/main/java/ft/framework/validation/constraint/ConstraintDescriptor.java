/*
 * Bean Validation API
 *
 * License: Apache License, Version 2.0
 * See the license.txt file in the root directory or <http://www.apache.org/licenses/LICENSE-2.0>.
 */
package ft.framework.validation.constraint;

import java.lang.annotation.Annotation;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.apache.commons.lang3.reflect.MethodUtils;

import ft.framework.validation.annotation.Constraint;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.SneakyThrows;

@Data
@AllArgsConstructor
public class ConstraintDescriptor<T extends Annotation> {
	
	private final T annotation;
	private final String message;
	private final List<Class<? extends ConstraintValidator<T, ?>>> constraintValidatorClasses;
	
	@SneakyThrows
	@SuppressWarnings("unchecked")
	public static <T extends Annotation> Optional<ConstraintDescriptor<T>> from(T annotation) {
		final var constraint = annotation.annotationType().getAnnotation(Constraint.class);
		if (constraint == null) {
			return Optional.empty();
		}
		
		final var message = (String) MethodUtils.invokeMethod(annotation, true, "message");
		final var constraintValidatorClasses = new ArrayList<Class<? extends ConstraintValidator<T, ?>>>();
		
		for (final var clazz : constraint.validatedBy()) {
			// TODO Check
			constraintValidatorClasses.add((Class<? extends ConstraintValidator<T, ?>>) clazz);
		}
		
		return Optional.of(new ConstraintDescriptor<>(annotation, message, constraintValidatorClasses));
	}
	
}