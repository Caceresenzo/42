package ft.app.matcha.domain.report;

import java.time.LocalDateTime;

import ft.app.matcha.domain.report.event.ReportedEvent;
import ft.app.matcha.domain.report.exception.CannotReportYourselfException;
import ft.app.matcha.domain.user.User;
import ft.framework.event.ApplicationEventPublisher;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class ReportService {
	
	private final ReportRepository repository;
	private final ApplicationEventPublisher eventPublisher;
	
	public Page<Report> findAll(User user, Pageable pageable) {
		return repository.findAllByUser(user, pageable);
	}
	
	public Report create(String reason, User user, User reporter) {
		if (user.getId() == reporter.getId()) {
			throw new CannotReportYourselfException();
		}
		
		final var report = repository.save(
			new Report()
				.setReason(reason)
				.setUser(user)
				.setReporter(reporter)
				.setCreatedAt(LocalDateTime.now())
		);
		
		eventPublisher.publishEvent(new ReportedEvent(this, report));
		
		return report;
	}
	
}