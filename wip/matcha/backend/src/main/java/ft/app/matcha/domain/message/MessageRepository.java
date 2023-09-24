package ft.app.matcha.domain.message;

import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class MessageRepository extends Repository<Message, Long> {
	
	public MessageRepository(EntityManager entityManager) {
		super(entityManager, Message.class);
	}
	
	public Page<Message> findAllBetweenTwoUser(User user1, User user2, Pageable pageable) {
		final var predicate = builder.or(
			builder.and(
				builder.equals(Message.Fields.user, user1),
				builder.equals(Message.Fields.peer, user2)
			),
			builder.and(
				builder.equals(Message.Fields.user, user2),
				builder.equals(Message.Fields.peer, user1)
			)
		);
		
		return findAllBy(predicate, pageable);
	}
	
}