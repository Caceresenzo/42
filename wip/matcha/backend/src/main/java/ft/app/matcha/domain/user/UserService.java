package ft.app.matcha.domain.user;

import java.util.Optional;

import ft.framework.orm.error.DuplicateValueException;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class UserService {
	
	private final UserRepository repository;
	
	public User create(String login, String password) {
		try {
			return repository.save(new User()
				.setLogin(login)
				.setPassword(password)
			);
		} catch (DuplicateValueException exception) {
			throw new LoginAlreadyTakenException(login);
		}
	}
	
	public Optional<User> find(String login, String password) {
		return repository.findByLoginAndPassword(login, password);
	}
	
}