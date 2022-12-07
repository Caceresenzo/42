package ft.framework.schedule.annotation;

import static java.lang.annotation.ElementType.METHOD;
import static java.lang.annotation.RetentionPolicy.RUNTIME;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;
import java.util.concurrent.TimeUnit;

@Retention(RUNTIME)
@Target(METHOD)
public @interface Scheduled {
	
	public static final String CRON_DISABLED = "-";
	
	String cron() default CRON_DISABLED;
	
	long fixedDelay() default 0;
	
	long initialDelay() default 0;
	
	TimeUnit timeUnit() default TimeUnit.MILLISECONDS;
	
}