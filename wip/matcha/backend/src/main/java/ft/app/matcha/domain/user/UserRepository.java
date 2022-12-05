package ft.app.matcha.domain.user;

import java.util.List;

import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class UserRepository extends Repository<User, Long> {
	
	public UserRepository(EntityManager entityManager) {
		super(entityManager, User.class);
	}
	
	public List<User> findAllByName(String name) {
		return findAllBy(
			builder.and(
				builder.equals(User.Fields.name, name),
				builder.isNotNull(User.Fields.bio)
			)
		);
	}
	
}