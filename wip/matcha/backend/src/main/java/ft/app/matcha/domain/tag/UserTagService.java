package ft.app.matcha.domain.tag;

import java.time.LocalDateTime;

import ft.app.matcha.configuration.MatchaConfigurationProperties;
import ft.app.matcha.domain.tag.exception.MaximumTagCountException;
import ft.app.matcha.domain.user.User;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;

public class UserTagService {
	
	private final UserTagRepository repository;
	private final long maxTagCount;
	
	public UserTagService(UserTagRepository repository, MatchaConfigurationProperties configurationProperties) {
		this.repository = repository;
		this.maxTagCount = configurationProperties.getMaximumTagCount();
	}
	
	public Page<Tag> findAll(User user, Pageable pageable) {
		return repository.findAllByUser(user, pageable).map(UserTag::getTag);
	}
	
	public Page<User> findAll(Tag tag, Pageable pageable) {
		return repository.findAllByTag(tag, pageable).map(UserTag::getUser);
	}
	
	public boolean add(User user, Tag tag) {
		final var existing = repository.findByUserAndTag(user, tag);
		if (existing.isPresent()) {
			return false;
		}
		
		final var count = repository.countByUserAndTag(user, tag);
		if (count >= maxTagCount) {
			throw new MaximumTagCountException(maxTagCount);
		}
		
		repository.save(
			new UserTag()
				.setUser(user)
				.setTag(tag)
				.setCreatedAt(LocalDateTime.now())
		);
		
		return true;
	}
	
	public boolean remove(User user, Tag tag) {
		return repository.deleteAllByUserAndTag(user, tag) != 0;
	}
	
	public long countByTag(Tag tag) {
		return repository.countByTag(tag);
	}
	
}