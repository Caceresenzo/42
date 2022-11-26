package ft.framework.validation.constraint.annotation;

import static java.lang.annotation.ElementType.FIELD;
import static java.lang.annotation.ElementType.PARAMETER;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import ft.framework.validation.annotation.Constraint;
import ft.framework.validation.constraint.validator.empty.NotEmptyCollectionValidator;
import ft.framework.validation.constraint.validator.empty.NotEmptyMapValidator;
import ft.framework.validation.constraint.validator.empty.NotEmptyStringValidator;

@Retention(RUNTIME)
@Target({ FIELD, PARAMETER })
@Constraint(validatedBy = {
	NotEmptyCollectionValidator.class,
	NotEmptyMapValidator.class,
	NotEmptyStringValidator.class
})
public @interface NotEmpty {
	
	String message() default "must not be empty";
	
}