package ft.framework.event.listener;

import ft.framework.event.ApplicationEvent;

public interface EventListener {
	
	boolean canAccept(Class<? extends ApplicationEvent> clazz);
	
	void accept(ApplicationEvent event);
	
}