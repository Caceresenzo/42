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
		@FieldValue("$handler") EntityHandler handler,
		@AllArguments Object[] arguments,
		@Origin Method method
	) throws Exception {
		final var methodName = method.getName();
		
		if (methodName.startsWith("set")) {
			final var fieldName = method.getName().substring(3);
			
			if (!handler.markModified(fieldName)) {
				handler.markAllModified();
			}
		} else if (!methodName.startsWith("get") && !EXCLUDED.contains(methodName)) {
			handler.markAllModified();
		}
		
		return method.invoke(handler.getOriginal(), arguments);
	}
	
}