package ft.app.matcha.controller;

import java.util.List;

import ft.app.matcha.entity.User;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.Parameter;
import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.RestController;
import ft.framework.orm.EntityManager;
import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@RestController(path = "/users")
public class UserController {
	
	private final EntityManager entityManager;
	
	@GetMapping
	public List<User> index() {
		return entityManager.findAll(User.class);
	}
	
	@GetMapping(path = "{id}")
	public User show(
		@Parameter long id
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