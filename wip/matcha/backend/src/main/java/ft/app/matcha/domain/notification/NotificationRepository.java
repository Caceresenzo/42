package ft.app.matcha.domain.notification;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class NotificationRepository extends Repository<Notification, Long> {
	
	public NotificationRepository(EntityManager entityManager) {
		super(entityManager, Notification.class);
	}
	
	public Page<Notification> findAllByUser(User user, Pageable pageable) {
		final var predicate = builder.equals(Notification.Fields.user, user);
		
		return findAllBy(predicate, pageable);
	}
	
	public Page<Notification> findAllByUserAndReadFalse(User user, Pageable pageable) {
		final var predicate = builder.and(
			builder.equals(Notification.Fields.user, user),
			builder.equals(Notification.Fields.read, false)
		);
		
		return findAllBy(predicate, pageable);
	}
	
}