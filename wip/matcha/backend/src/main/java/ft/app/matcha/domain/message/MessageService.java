package ft.app.matcha.domain.message;

import java.time.LocalDateTime;

import ft.app.matcha.domain.message.event.MessageCreatedEvent;
import ft.app.matcha.domain.message.exception.MessageYourselfException;
import ft.app.matcha.domain.message.exception.NotConnectedException;
import ft.app.matcha.domain.relationship.RelationshipService;
import ft.app.matcha.domain.user.User;
import ft.framework.event.ApplicationEventPublisher;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class MessageService {
	
	private final MessageRepository repository;
	private final ApplicationEventPublisher eventPublisher;
	private final RelationshipService relationshipService;
	
	public Page<Message> findAll(User user1, User user2, Pageable pageable) {
		return repository.findAllBetweenTwoUser(user1, user2, pageable);
	}
	
	public Message create(User user, User peer, String content) {
		if (user.getId() == peer.getId()) {
			throw new MessageYourselfException();
		}
		
		if (!relationshipService.areConnected(user, peer)) {
			throw new NotConnectedException();
		}
		
		final var message = repository.save(
			new Message()
				.setUser(user)
				.setPeer(peer)
				.setContent(content)
				.setCreatedAt(LocalDateTime.now())
		);
		
		eventPublisher.publishEvent(new MessageCreatedEvent(this, message));
		
		return message;
	}
	
	// @Scheduled(fixedDelay = 1000)
	public void fake() {
		create(new User().setId(1), new User().setId(2), "Hey its %s!".formatted(System.currentTimeMillis()));
	}
	
}