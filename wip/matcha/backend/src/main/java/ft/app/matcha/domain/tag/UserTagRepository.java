package ft.app.matcha.domain.tag;

import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.predicate.Predicate;
import ft.framework.orm.repository.Repository;

public class UserTagRepository extends Repository<UserTag, Long> {
	
	public UserTagRepository(EntityManager entityManager) {
		super(entityManager, UserTag.class);
	}
	
	public Page<UserTag> findAllByUser(User user, Pageable pageable) {
		return findAllBy(builder.equals(UserTag.Fields.user, user), pageable);
	}
	
	public Page<UserTag> findAllByTag(Tag tag, Pageable pageable) {
		return findAllBy(builder.equals(UserTag.Fields.tag, tag), pageable);
	}
	
	public Optional<UserTag> findByUserAndTag(User user, Tag tag) {
		return findBy(createByUserAndTagPredicate(user, tag));
	}
	
	public long countByUserAndTag(User user, Tag tag) {
		return countBy(createByUserAndTagPredicate(user, tag));
	}
	
	public long deleteAllByUserAndTag(User user, Tag tag) {
		return deleteAllBy(createByUserAndTagPredicate(user, tag));
	}
	
	public long countByTag(Tag tag) {
		return countBy(builder.equals(UserTag.Fields.tag, tag));
	}
	
	public Predicate<UserTag> createByUserAndTagPredicate(User user, Tag tag) {
		return builder.and(
			builder.equals(UserTag.Fields.user, user),
			builder.equals(UserTag.Fields.tag, tag)
		);
	}
	
}