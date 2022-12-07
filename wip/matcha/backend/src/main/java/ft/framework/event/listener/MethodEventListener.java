package ft.framework.event.listener;

import java.lang.reflect.Method;
import java.lang.reflect.Parameter;

import org.apache.commons.lang3.reflect.MethodUtils;

import ft.framework.event.ApplicationEvent;
import lombok.SneakyThrows;

public class MethodEventListener implements EventListener {
	
	public static final Object[] EMPTY = new Object[0];
	
	private final Object object;
	private final Method method;
	private final Parameter parameter;
	
	public MethodEventListener(Object object, Method method) {
		this.object = object;
		this.method = method;
		
		final var parameters = method.getParameters();
		if (parameters.length == 0) {
			parameter = null;
		} else if (parameters.length == 1) {
			parameter = parameters[0];
		} else {
			throw new IllegalArgumentException("method " + method + " should only have zero or one parameter");
		}
	}
	
	@Override
	public boolean canAccept(Class<? extends ApplicationEvent> clazz) {
		if (parameter == null) {
			return true;
		}
		
		return parameter.getType().isAssignableFrom(clazz);
	}
	
	@SneakyThrows
	@Override
	public void accept(ApplicationEvent event) {
		var arguments = EMPTY;
		
		if (parameter != null) {
			arguments = new Object[] { event };
		}
		
		MethodUtils.getAccessibleMethod(method)
			.invoke(object, arguments);
	}
	
}