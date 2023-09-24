package ft.app.matcha.domain.visit;

import java.time.LocalDate;
import java.time.LocalTime;

import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.visit.event.VisitedEvent;
import ft.framework.event.ApplicationEventPublisher;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class VisitService {
	
	private final VisitRepository repository;
	private final ApplicationEventPublisher eventPublisher;
	
	public Visit log(User user, User viewer) {
		final var date = LocalDate.now();
		final var time = LocalTime.now();
		
		final var optional = repository.findByUserAndViewerAndDate(user, viewer, date);
		if (optional.isPresent()) {
			final var visit = optional.get();
			
			visit
				.setTimes(visit.getTimes() + 1)
				.setLastAt(time);
			
			return repository.save(visit);
		}
		
		final var visit = repository.save(
			new Visit()
				.setUser(user)
				.setViewer(viewer)
				.setDate(date)
				.setTimes(1)
				.setFirstAt(time)
				.setLastAt(time)
		);
		
		eventPublisher.publishEvent(new VisitedEvent(this, visit));
		
		return visit;
	}
	
	public Page<Visit> findAll(User user, Pageable pageable) {
		return repository.findAllByUser(user, pageable);
	}
	
}