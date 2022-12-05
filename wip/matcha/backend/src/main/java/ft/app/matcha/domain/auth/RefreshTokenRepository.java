package ft.app.matcha.domain.auth;

import java.time.LocalDateTime;
import java.util.Optional;

import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class RefreshTokenRepository extends Repository<RefreshToken, Long> {
	
	public RefreshTokenRepository(EntityManager entityManager) {
		super(entityManager, RefreshToken.class);
	}
	
	public Optional<RefreshToken> findByEncoded(String encrypted) {
		return findBy(
			builder.equals(RefreshToken.Fields.encoded, encrypted)
		);
	}
	
	public long deleteAllByExpireAtLessThan(LocalDateTime dateTime) {
		return deleteAllBy(
			builder.lessThan(RefreshToken.Fields.expireAt, dateTime)
		);
	}
	
}