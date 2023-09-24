package ft.app.matcha.domain.report;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class ReportRepository extends Repository<Report, Long> {
	
	public ReportRepository(EntityManager entityManager) {
		super(entityManager, Report.class);
	}
	
	public Page<Report> findAllByUser(User user, Pageable pageable) {
		final var predicate = builder.equals(Report.Fields.user, user);
		
		return findAllBy(predicate, pageable);
	}
	
}