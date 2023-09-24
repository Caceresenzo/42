package ft.app.matcha.domain.user;

import java.util.List;
import java.util.Optional;

import ft.framework.orm.EntityManager;
import ft.framework.orm.repository.Repository;

public class UserRepository extends Repository<User, Long> {
	
	public UserRepository(EntityManager entityManager) {
		super(entityManager, User.class);
	}
	
	public List<User> findAllByName(String name) {
		return findAllBy(
			builder.and(
				builder.equals(User.Fields.login, name),
				builder.isNotNull(User.Fields.biography)
			)
		);
	}
	
	public Optional<User> findByEmail(String email) {
		return findBy(
			builder.equals(User.Fields.email, email)
		);
	}
	
	public Optional<User> findByLoginAndPassword(String login, String password) {
		return findBy(
			builder.and(
				builder.equals(User.Fields.login, login),
				builder.equals(User.Fields.password, password)
			)
		);
	}
	
	public List<User> findAllMen() {
		return findAllBy(builder.equals(User.Fields.gender, Gender.MAN));
	}
	
	public boolean existsByEmail(String email) {
		return existsBy(builder.equals(User.Fields.email, email));
	}
	
}