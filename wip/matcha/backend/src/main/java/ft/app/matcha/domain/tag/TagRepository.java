package ft.app.matcha.domain.tag;

import java.util.Optional;

import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class TagRepository extends Repository<Tag, Long> {
	
	public TagRepository(EntityManager entityManager) {
		super(entityManager, Tag.class);
	}
	
	public Optional<Tag> findByName(String name) {
		return findBy(builder.equals(Tag.Fields.name, name));
	}

	public Page<Tag> findAllByNameLike(String name, Pageable pageable) {
		return findAllBy(builder.likeWildcard(Tag.Fields.name, name), pageable);
	}
	
}