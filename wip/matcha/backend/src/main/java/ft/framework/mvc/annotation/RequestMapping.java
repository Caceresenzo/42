package ft.framework.mvc.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Inherited;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import ft.framework.util.MediaTypes;
import spark.route.HttpMethod;

@Inherited
@Retention(RetentionPolicy.RUNTIME)
@Target({ ElementType.METHOD, ElementType.TYPE, ElementType.ANNOTATION_TYPE })
public @interface RequestMapping {
	
	HttpMethod method() default HttpMethod.unsupported;
	
	String path() default "";
	
	String consume() default MediaTypes.JSON;
	
	String produce() default MediaTypes.JSON;
	
}