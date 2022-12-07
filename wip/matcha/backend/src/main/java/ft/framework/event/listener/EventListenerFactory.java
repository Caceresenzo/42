package ft.framework.event.listener;

import org.apache.commons.lang3.reflect.MethodUtils;

import ft.framework.event.ApplicationEventPublisher;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@RequiredArgsConstructor
public class EventListenerFactory {
	
	private final ApplicationEventPublisher eventPublisher;
	
	public <T> T scan(T object) {
		final var methods = MethodUtils.getMethodsListWithAnnotation(object.getClass(), ft.framework.event.annotation.EventListener.class);
		
		if (!methods.isEmpty()) {
			log.info("Found {} listener(s) on {}", methods.size(), object);
			
			for (final var method : methods) {
				eventPublisher.addListener(new MethodEventListener(object, method));
			}
		}
		
		return object;
	}
	
}