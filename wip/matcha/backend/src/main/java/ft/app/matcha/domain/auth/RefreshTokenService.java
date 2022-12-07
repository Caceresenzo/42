package ft.app.matcha.domain.auth;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.Optional;
import java.util.concurrent.TimeUnit;

import org.apache.commons.lang3.RandomStringUtils;

import ft.app.matcha.domain.user.User;
import ft.framework.schedule.annotation.Scheduled;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class RefreshTokenService {
	
	public static final int LENGTH = 128;
	public static final Duration EXPIRATION = Duration.ofDays(7);
	
	private final RefreshTokenRepository repository;
	
	public RefreshToken create(User user) {
		final var plain = RandomStringUtils.randomAlphanumeric(LENGTH);
		final var encoded = encode(plain);
		
		final var createdAt = LocalDateTime.now();
		final var expiredAt = createdAt.plus(EXPIRATION);
		
		return repository.save(new RefreshToken()
			.setUser(user)
			.setEncoded(encoded)
			.setPlain(plain)
			.setCreatedAt(createdAt)
			.setExpireAt(expiredAt)
		);
	}
	
	public Optional<RefreshToken> refresh(String plain) {
		final var previous = find(plain);
		
		previous.ifPresent(repository::delete);
		
		return previous
			.map(RefreshToken::getUser)
			.map(this::create);
	}
	
	public Optional<RefreshToken> find(String plain) {
		final var encoded = encode(plain);
		
		return repository.findByEncoded(encoded);
	}
	
	public void delete(RefreshToken refreshToken) {
		repository.delete(refreshToken);
	}
	
	@Scheduled(fixedDelay = 60, timeUnit = TimeUnit.SECONDS)
	public long deleteExpired() {
		return repository.deleteAllByExpireAtLessThan(LocalDateTime.now());
	}
	
	public static String encode(String plain) {
		return PasswordEncoder.encode(plain);
	}
	
}