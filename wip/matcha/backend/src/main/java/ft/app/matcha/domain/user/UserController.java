package ft.app.matcha.domain.user;

import java.util.List;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.EntityManager;
import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/users")
public class UserController {
	
	private final EntityManager entityManager;
	
	@GetMapping
	public List<User> index(Pageable pageable) {
		return entityManager.findAll(User.class);
	}
	
	@PostMapping
	public User create(
		@Body UserCreateForm body
	) {
		return entityManager.insert(new User()
			.setName(body.getName())
			.setBio(body.getBio()));
	}
	
	@GetMapping(path = "{id}")
	public User show(
		@Variable long id
	) {
		return entityManager.find(User.class, id)
			.orElseThrow(() -> new UserNotFoundException(id));
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