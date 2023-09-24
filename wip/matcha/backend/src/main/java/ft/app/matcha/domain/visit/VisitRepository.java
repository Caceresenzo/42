package ft.app.matcha.domain.visit;

import java.time.LocalDate;
import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class VisitRepository extends Repository<Visit, Long> {
	
	public VisitRepository(EntityManager entityManager) {
		super(entityManager, Visit.class);
	}
	
	public Page<Visit> findAllByUser(User user, Pageable pageable) {
		final var predicate = builder.and(
			builder.equals(Visit.Fields.user, user)
		);
		
		return findAllBy(predicate, pageable);
	}
	
	public Optional<Visit> findByUserAndViewerAndDate(User user, User viewer, LocalDate date) {
		final var predicate = builder.and(
			builder.equals(Visit.Fields.user, user),
			viewer != null
				? builder.equals(Visit.Fields.viewer, viewer)
				: builder.isNull(Visit.Fields.viewer),
			builder.equals(Visit.Fields.date, date)
		);
		
		/* null columns are not working with unique contraint */
		return findFirstBy(predicate);
	}
	
}