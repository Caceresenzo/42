package ft.app.matcha.domain.relationship;

import java.time.LocalDateTime;
import java.util.Optional;

import ft.app.matcha.domain.relationship.event.BlockedEvent;
import ft.app.matcha.domain.relationship.event.LikedEvent;
import ft.app.matcha.domain.relationship.event.UnlikedEvent;
import ft.app.matcha.domain.relationship.exception.CannotBlockYourselfException;
import ft.app.matcha.domain.relationship.exception.CannotLikeBlockedUserException;
import ft.app.matcha.domain.relationship.exception.CannotLikeYourselfException;
import ft.app.matcha.domain.report.event.ReportedEvent;
import ft.app.matcha.domain.user.User;
import ft.framework.event.ApplicationEventPublisher;
import ft.framework.event.annotation.EventListener;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class RelationshipService {
	
	private final RelationshipRepository repository;
	private final ApplicationEventPublisher eventPublisher;
	
	public Optional<Relationship> find(User user, User peer) {
		return repository.findByUserAndPeer(user, peer);
	}
	
	public Page<Relationship> findAllByUser(User user, Relationship.Type type, Pageable pageable) {
		return repository.findAllByUserAndType(user, type, pageable);
	}
	
	public Page<Relationship> findAllByPeer(User peer, Relationship.Type type, Pageable pageable) {
		return repository.findAllByPeerAndType(peer, type, pageable);
	}
	
	public Relationship block(User user, User peer) {
		if (user.getId() == peer.getId()) {
			throw new CannotBlockYourselfException();
		}
		
		final var optional = repository.findByUserAndPeer(user, peer);
		if (optional.isPresent()) {
			final var relationship = optional.get();
			
			switch (relationship.getType()) {
				case BLOCK: {
					return relationship;
				}
				
				case LIKE: {
					repository.save(
						relationship
							.setType(Relationship.Type.BLOCK)
							.setCreatedAt(LocalDateTime.now())
					);
					
					eventPublisher.publishEvent(new BlockedEvent(this, user, peer));
					
					return relationship;
				}
				
				default: {
					throw new IllegalArgumentException("Unexpected value: " + relationship.getType());
				}
			}
		}
		
		final var block = repository.save(
			new Relationship()
				.setUser(user)
				.setPeer(peer)
				.setType(Relationship.Type.BLOCK)
				.setCreatedAt(LocalDateTime.now())
		);
		
		eventPublisher.publishEvent(new BlockedEvent(this, user, peer));
		
		return block;
	}
	
	public Relationship like(User user, User peer) {
		if (user.getId() == peer.getId()) {
			throw new CannotLikeYourselfException();
		}
		
		final var optional = repository.findByUserAndPeer(user, peer);
		if (optional.isPresent()) {
			final var relationship = optional.get();
			
			return switch (relationship.getType()) {
				case LIKE -> relationship;
				case BLOCK -> throw new CannotLikeBlockedUserException();
				default -> throw new IllegalArgumentException("Unexpected value: " + relationship.getType());
			};
		}
		
		final var like = repository.save(
			new Relationship()
				.setUser(user)
				.setPeer(peer)
				.setType(Relationship.Type.LIKE)
				.setCreatedAt(LocalDateTime.now())
		);
		
		final var cross = repository.existsByUserAndPeerAndType(peer, user, Relationship.Type.LIKE);
		eventPublisher.publishEvent(new LikedEvent(this, user, peer, cross));
		
		return like;
	}
	
	public boolean unlike(User user, User peer) {
		final var unliked = repository.deleteByUserAndPeerAndType(user, peer, Relationship.Type.LIKE) != 0;
		
		if (unliked) {
			eventPublisher.publishEvent(new UnlikedEvent(this, user, peer));
		}
		
		return unliked;
	}
	
	public boolean unblock(User user, User peer) {
		return repository.deleteByUserAndPeerAndType(user, peer, Relationship.Type.BLOCK) != 0;
	}
	
	public boolean isBlocked(User user, User peer) {
		return repository.existsByUserAndPeerAndType(user, peer, Relationship.Type.BLOCK);
	}
	
	public boolean isLiked(User user, User peer) {
		return repository.existsByUserAndPeerAndType(user, peer, Relationship.Type.LIKE);
	}
	
	public boolean isMutual(Relationship relationship) {
		return repository.existsByUserAndPeerAndType(relationship.getUser(), relationship.getPeer(), relationship.getType());
	}
	
	public boolean areConnected(User user, User peer) {
		return isLiked(user, peer) && isLiked(peer, user);
	}
	
	@EventListener
	public void onReported(ReportedEvent event) {
		final var report = event.getReport();
		
		final var user = report.getReporter();
		final var peer = report.getUser();
		
		block(user, peer);
	}
	
}