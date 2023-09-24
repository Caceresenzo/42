package ft.app.matcha.domain.user;

import java.time.LocalDateTime;
import java.util.Optional;

import ft.app.matcha.configuration.MatchaConfigurationProperties;
import ft.app.matcha.domain.relationship.event.BlockedEvent;
import ft.app.matcha.domain.relationship.event.LikedEvent;
import ft.app.matcha.domain.relationship.event.UnlikedEvent;
import ft.app.matcha.domain.report.event.ReportedEvent;
import ft.app.matcha.domain.user.exception.EmailAlreadyUsedException;
import ft.app.matcha.domain.user.exception.LoginAlreadyTakenException;
import ft.framework.event.annotation.EventListener;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.error.DuplicateValueException;
import ft.framework.orm.mapping.contraint.Constraint;

public class UserService {
	
	private final UserRepository repository;
	private final FameValues fameValues;
	
	public UserService(UserRepository repository, MatchaConfigurationProperties properties) {
		this.repository = repository;
		
		this.fameValues = new FameValues(
			properties.getFameOnLike(),
			properties.getFameOnUnlike(),
			properties.getFameOnBlock(),
			properties.getFameOnReport()
		);
	}
	
	public User create(String firstName, String lastName, String email, String login, String password, boolean emailConfirmed) {
		try {
			return repository.save(new User()
				.setFirstName(firstName)
				.setLastName(lastName)
				.setEmail(email)
				.setLogin(login)
				.setPassword(password)
				.setEmailConfirmed(emailConfirmed)
				.setEmailConfirmedAt(emailConfirmed ? LocalDateTime.now() : null)
			);
		} catch (DuplicateValueException exception) {
			final var unique = Optional.ofNullable(exception.getConstraint()).map(Constraint::getName).orElse("");
			
			if (unique.contains(User.Fields.email)) {
				throw new EmailAlreadyUsedException(email);
			}
			
			throw new LoginAlreadyTakenException(login);
		}
	}
	
	public Page<User> findAll(Pageable pageable) {
		return repository.findAll(pageable);
	}
	
	public Optional<User> find(Long id) {
		return repository.findById(id);
	}
	
	public Optional<User> find(String email) {
		return repository.findByEmail(email);
	}
	
	public boolean exists(String email) {
		return repository.existsByEmail(email);
	}
	
	public Optional<User> find(String login, String password) {
		return repository.findByLoginAndPassword(login, password);
	}
	
	public User save(User user) {
		return repository.save(user);
	}
	
	@EventListener
	public void onLiked(LikedEvent event) {
		final var user = event.getPeer();
		
		changeFame(user, fameValues.onLike());
	}
	
	@EventListener
	public void onUnliked(UnlikedEvent event) {
		final var user = event.getPeer();
		
		changeFame(user, fameValues.onUnlike());
	}
	
	@EventListener
	public void onBlocked(BlockedEvent event) {
		final var user = event.getPeer();
		
		changeFame(user, fameValues.onBlock());
	}
	
	@EventListener
	public void onReported(ReportedEvent event) {
		final var user = event.getReport().getUser();
		
		changeFame(user, fameValues.onReport());
	}
	
	public User changeFame(User user, int change) {
		return repository.save(user.setFame(user.getFame() + change));
	}
	
	static record FameValues(
		int onLike,
		int onUnlike,
		int onBlock,
		int onReport
	) {}
	
}