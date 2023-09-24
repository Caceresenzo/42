package ft.app.matcha.domain.auth;

import java.time.LocalDateTime;
import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class TokenRepository extends Repository<Token, Long> {
	
	public TokenRepository(EntityManager entityManager) {
		super(entityManager, Token.class);
	}
	
	public Optional<Token> findByTypeAndEncoded(Token.Type type, String encrypted) {
		return findBy(
			builder.and(
				builder.equals(Token.Fields.type, type),
				builder.equals(Token.Fields.encoded, encrypted)
			)
		);
	}
	
	public long deleteAllByExpireAtLessThan(LocalDateTime dateTime) {
		return deleteAllBy(
			builder.lessThan(Token.Fields.expireAt, dateTime)
		);
	}
	
	public long deleteAllByUser(User user) {
		return deleteAllBy(
			builder.equals(Token.Fields.user, user)
		);
	}
	
}