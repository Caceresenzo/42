package ft.framework.validation.constraint.annotation;

import static java.lang.annotation.ElementType.FIELD;
import static java.lang.annotation.ElementType.PARAMETER;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import ft.framework.validation.annotation.Constraint;
import ft.framework.validation.constraint.validator.PositiveOrZeroValidator;

@Retention(RUNTIME)
@Target({ FIELD, PARAMETER })
@Constraint(validatedBy = PositiveOrZeroValidator.class)
public @interface PositiveOrZero {

	String message() default "must be positive or zero";
	
}