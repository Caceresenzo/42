package ft.app.matcha.domain.user;

import java.util.Optional;

import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class UserService {
	
	private final UserRepository repository;
	
	public User create(String login, String password) {
		return repository.save(new User()
			.setLogin(login)
			.setPassword(password)
		);
	}
	
	public Optional<User> find(String login, String password) {
		return repository.findByLoginAndPassword(login, password);
	}
	
}