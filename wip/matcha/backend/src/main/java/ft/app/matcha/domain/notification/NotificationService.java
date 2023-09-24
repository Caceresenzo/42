package ft.app.matcha.domain.notification;

import java.time.LocalDateTime;
import java.util.Optional;

import org.apache.commons.lang3.tuple.Pair;

import ft.app.matcha.domain.auth.event.RegisterEvent;
import ft.app.matcha.domain.message.event.MessageCreatedEvent;
import ft.app.matcha.domain.notification.event.NotificationCreatedEvent;
import ft.app.matcha.domain.relationship.RelationshipService;
import ft.app.matcha.domain.relationship.event.LikedEvent;
import ft.app.matcha.domain.relationship.event.UnlikedEvent;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.visit.event.VisitedEvent;
import ft.framework.event.ApplicationEventPublisher;
import ft.framework.event.annotation.EventListener;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class NotificationService {
	
	private final NotificationRepository repository;
	private final RelationshipService relationshipService;
	private final ApplicationEventPublisher eventPublisher;
	
	public Optional<Notification> find(long id) {
		return repository.findById(id);
	}
	
	public Page<Notification> findAll(User user, boolean includeAll, Pageable pageable) {
		if (includeAll) {
			return repository.findAllByUser(user, pageable);
		}
		
		return repository.findAllByUserAndReadFalse(user, pageable);
	}
	
	public Notification create(User user, Notification.Type type, String content, String link) {
		final var notification = repository.save(
			new Notification()
				.setUser(user)
				.setType(type)
				.setContent(content)
				.setLink(link)
				.setCreatedAt(LocalDateTime.now())
		);
		
		eventPublisher.publishEvent(new NotificationCreatedEvent(this, notification));
		
		return notification;
	}
	
	public Notification create(User user, Notification.Type type, Pair<String, String> contentAndLink) {
		return create(user, type, contentAndLink.getLeft(), contentAndLink.getRight());
	}
	
	public Notification save(Notification notification) {
		return repository.save(notification);
	}
	
	@EventListener
	public void onRegister(RegisterEvent event) {
		final var user = event.getUser();
		
		create(user, Notification.Type.WELCOME, "Welcome!", null);
	}
	
	/* The user received a "like". */
	@EventListener
	public void onLike(LikedEvent event) {
		if (event.isCross()) {
			return;
		}
		
		final var user = event.getUser();
		final var peer = event.getPeer();
		
		if (canCreate(peer, user)) {
			create(peer, Notification.Type.LIKED, NotificationFormatter.formatLiked(user));
		}
	}
	
	/* The user's profile has been checked. */
	@EventListener
	public void onVisited(VisitedEvent event) {
		final var visit = event.getVisit();
		final var user = visit.getUser();
		final var viewer = visit.getViewer();
		
		/* do not include anonymous visits */
		if (viewer != null && canCreate(user, viewer)) {
			create(user, Notification.Type.PROFILE_CHECKED, NotificationFormatter.formatProfileChecked(viewer));
		}
	}
	
	/* The user received a message. */
	@EventListener
	public void onMessageCreated(MessageCreatedEvent event) {
		final var message = event.getMessage();
		final var user = message.getUser();
		final var peer = message.getPeer();
		
		if (canCreate(peer, user)) {
			create(peer, Notification.Type.MESSAGE_RECEIVED, NotificationFormatter.formatMessageReceived(message));
		}
	}
	
	/* A "liked" user "liked" back. */
	@EventListener
	public void onLikeBack(LikedEvent event) {
		if (!event.isCross()) {
			return;
		}
		
		final var user = event.getUser();
		final var peer = event.getPeer();
		
		if (canCreate(peer, user)) {
			create(peer, Notification.Type.LIKED_BACK, NotificationFormatter.formatLikedBack(user));
		}
	}
	
	/* A connected user "unliked" you. */
	@EventListener
	public void onUnliked(UnlikedEvent event) {
		final var user = event.getUser();
		final var peer = event.getPeer();
		
		if (canCreate(peer, user)) {
			create(peer, Notification.Type.UNLIKED, NotificationFormatter.formatUnliked(user));
		}
	}
	
	public boolean canCreate(User user, User peer) {
		return !relationshipService.isBlocked(user, peer);
	}
	
}