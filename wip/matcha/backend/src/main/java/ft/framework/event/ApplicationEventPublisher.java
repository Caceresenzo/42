package ft.framework.event;

import java.util.ArrayList;
import java.util.List;

import ft.framework.event.listener.EventListener;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ApplicationEventPublisher {
	
	private final List<EventListener> listeners = new ArrayList<>(16);
	
	public void publishEvent(ApplicationEvent event) {
		final var clazz = event.getClass();
		
		final var filtered = filterListeners(clazz);
		
		log.info("Dispatching event '{}' to {} listener(s)", clazz.getName(), filtered.size());
		
		for (final var listener : filtered) {
			try {
				listener.accept(event);
			} catch (Throwable throwable) {
				throw new ApplicationEventException("could not dispatch event", throwable);
			}
		}
	}
	
	private List<EventListener> filterListeners(Class<? extends ApplicationEvent> clazz) {
		return listeners.stream()
			.filter((listener) -> listener.canAccept(clazz))
			.toList();
	}
	
	public void addListener(EventListener listener) {
		listeners.add(listener);
	}
	
}