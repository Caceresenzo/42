package ft.app.matcha.domain.user;

import java.util.List;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/users")
public class UserController {
	
	private final UserRepository repository;
	
	@GetMapping
	public Page<User> index(Pageable pageable) {
		return repository.findAll(pageable);
	}
	
	@PostMapping
	public User create(
		@Body UserCreateForm body
	) {
		return repository.save(new User()
			.setLogin(body.getName())
			.setBio(body.getBio()));
	}
	
	@GetMapping(path = "{id}")
	public User show(
		@Variable long id
	) {
		return repository.findById(id)
			.orElseThrow(() -> new UserNotFoundException(id));
	}
	
	@GetMapping(path = "/name/{name}")
	public List<User> show(
		@Variable String name
	) {
		return repository.findAllByName(name);
	}
	
	@SuppressWarnings("serial")
	@Getter
	public static class UserNotFoundException extends RuntimeException {
		
		@ResponseErrorProperty
		private final long id;
		
		public UserNotFoundException(long id) {
			super("no user found for this id");
			
			this.id = id;
		}
		
	}
	
}