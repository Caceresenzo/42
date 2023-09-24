package ft.app.matcha.domain.relationship;

import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class RelationshipRepository extends Repository<Relationship, Long> {
	
	public RelationshipRepository(EntityManager entityManager) {
		super(entityManager, Relationship.class);
	}
	
	public Optional<Relationship> findByUserAndPeer(User user, User peer) {
		return findBy(builder.and(
			builder.equals(Relationship.Fields.user, user),
			builder.equals(Relationship.Fields.peer, peer)
		));
	}
	
	public boolean existsByUserAndPeerAndType(User user, User peer, Relationship.Type type) {
		return existsBy(builder.and(
			builder.equals(Relationship.Fields.user, user),
			builder.equals(Relationship.Fields.peer, peer),
			builder.equals(Relationship.Fields.type, type)
		));
	}
	
	public Page<Relationship> findAllByUser(User user, Pageable pageable) {
		return findAllBy(builder.and(
			builder.equals(Relationship.Fields.user, user)
		), pageable);
	}
	
	public Page<Relationship> findAllByUserAndType(User user, Relationship.Type type, Pageable pageable) {
		return findAllBy(builder.and(
			builder.equals(Relationship.Fields.user, user),
			builder.equals(Relationship.Fields.type, type)
		), pageable);
	}
	
	public Page<Relationship> findAllByPeerAndType(User peer, Relationship.Type type, Pageable pageable) {
		return findAllBy(builder.and(
			builder.equals(Relationship.Fields.peer, peer),
			builder.equals(Relationship.Fields.type, type)
		), pageable);
	}
	
	public long deleteByUserAndPeerAndType(User user, User peer, Relationship.Type type) {
		return deleteAllBy(builder.and(
			builder.equals(Relationship.Fields.user, user),
			builder.equals(Relationship.Fields.peer, peer),
			builder.equals(Relationship.Fields.type, type)
		));
	}
	
}