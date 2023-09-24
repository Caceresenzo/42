package ft.app.matcha.domain.heartbeat;

import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class HeartbeatRepository extends Repository<Heartbeat, Long> {
	
	public HeartbeatRepository(EntityManager entityManager) {
		super(entityManager, Heartbeat.class);
	}
	
	public Optional<Heartbeat> findByUser(User user) {
		return findBy(
			builder.equals(Heartbeat.Fields.user, user)
		);
	}
	
}