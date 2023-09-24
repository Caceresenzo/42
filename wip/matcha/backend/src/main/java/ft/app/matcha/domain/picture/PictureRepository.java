package ft.app.matcha.domain.picture;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class PictureRepository extends Repository<Picture, Long> {
	
	public PictureRepository(EntityManager entityManager) {
		super(entityManager, Picture.class);
	}
	
	public Page<Picture> findAllByUser(User user, Pageable pageable) {
		return findAllBy(builder.equals(Picture.Fields.user, user), pageable);
	}
	
	public long countByUser(User user) {
		return countBy(builder.equals(Picture.Fields.user, user));
	}
	
}