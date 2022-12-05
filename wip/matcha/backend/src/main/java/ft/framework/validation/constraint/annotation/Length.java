package ft.framework.validation.constraint.annotation;

import static java.lang.annotation.ElementType.FIELD;
import static java.lang.annotation.ElementType.PARAMETER;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import ft.framework.validation.annotation.Constraint;
import ft.framework.validation.constraint.validator.LengthValidator;

@Retention(RUNTIME)
@Target({ FIELD, PARAMETER })
@Constraint(validatedBy = LengthValidator.class)
public @interface Length {
	
	public static final int UNSPECIFIED = -1;
	
	int min() default UNSPECIFIED;
	
	int max() default UNSPECIFIED;
	
	String message() default "must have the correct length";
	
}