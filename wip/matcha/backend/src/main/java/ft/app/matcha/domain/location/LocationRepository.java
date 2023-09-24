package ft.app.matcha.domain.location;

import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class LocationRepository extends Repository<Location, User> {
	
	public LocationRepository(EntityManager entityManager) {
		super(entityManager, Location.class);
	}
	
	public Optional<Location> findByUser(User user) {
		return findBy(builder.equals(Location.Fields.user, user));
	}
	
}