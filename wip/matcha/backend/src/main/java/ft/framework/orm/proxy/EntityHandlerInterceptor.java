package ft.framework.orm.proxy;

import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.List;

import net.bytebuddy.implementation.bind.annotation.AllArguments;
import net.bytebuddy.implementation.bind.annotation.FieldValue;
import net.bytebuddy.implementation.bind.annotation.Origin;
import net.bytebuddy.implementation.bind.annotation.RuntimeType;
import net.bytebuddy.implementation.bind.annotation.This;

public class EntityHandlerInterceptor {
	
	public static final List<String> EXCLUDED = Arrays.asList(
		"toString",
		"hashCode",
		"equals");
	
	@RuntimeType
	public static Object intercept(
		@This Object self,
		@FieldValue(ProxiedEntity.HANDLER_FIELD) EntityHandler handler,
		@AllArguments Object[] arguments,
		@Origin Method method
	) throws Exception {
		final var isGetter = isGetter(method);
		
		if (!handler.isInitialized()) {
			if (isGetter) {
				final var fieldName = getFieldName(method);
				
				if (handler.isMatchingIdColumn(fieldName)) {
					return handler.getId();
				}
			}
			
			handler.fetchLazy();
		}
		
		if (isSetter(method)) {
			final var fieldName = getFieldName(method);
			
			if (!handler.markModified(fieldName)) {
				handler.markAllModified();
			}
		} else if (!isGetter && !isBooleanGetter(method) && !isExcluded(method)) {
			handler.markAllModified();
		}
		
		final var returnValue = method.invoke(handler.getOriginal(), arguments);
		if (returnValue == handler.getOriginal()) {
			return self;
		}
		
		return returnValue;
	}
	
	public static boolean isGetter(Method method) {
		return method.getName().startsWith("get");
	}
	
	public static boolean isBooleanGetter(Method method) {
		return method.getName().startsWith("is");
	}
	
	public static boolean isExcluded(Method method) {
		return EXCLUDED.contains(method.getName());
	}
	
	public static boolean isSetter(Method method) {
		return method.getName().startsWith("set");
	}
	
	public static String getFieldName(Method method) {
		return method.getName().substring(3);
	}
	
}