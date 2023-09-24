package ft.app.matcha.domain.picture;

import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class DefaultPictureRepository extends Repository<DefaultPicture, Long> {
	
	public DefaultPictureRepository(EntityManager entityManager) {
		super(entityManager, DefaultPicture.class);
	}
	
	public Optional<DefaultPicture> findByUser(User user) {
		return findBy(
			builder.equals(DefaultPicture.Fields.user, user)
		);
	}
	
}