package ft.framework.orm.annotation;

import static java.lang.annotation.ElementType.FIELD;
import static java.lang.annotation.ElementType.METHOD;
import static java.lang.annotation.ElementType.TYPE;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;

@Target({ METHOD, FIELD, TYPE })
@Retention(RUNTIME)
public @interface OnDelete {
	
	Action action() default Action.RESTRICT;
	
	public enum Action {
		
		RESTRICT,
		SET_NULL,
		NO_ACTION,
		CASCADE;
	
	}
	
}