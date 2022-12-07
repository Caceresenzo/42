package ft.app.matcha.domain.notification;

import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class NotificationRepository extends Repository<Notification, Long> {
	
	public NotificationRepository(EntityManager entityManager) {
		super(entityManager, Notification.class);
	}
	
}