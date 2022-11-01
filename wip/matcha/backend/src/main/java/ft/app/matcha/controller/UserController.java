package ft.app.matcha.controller;

import java.util.List;
import java.util.UUID;
import java.util.stream.IntStream;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.Parameter;
import ft.framework.mvc.annotation.PatchMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.ResponseStatus;
import ft.framework.mvc.annotation.RestController;
import lombok.Data;
import lombok.experimental.Accessors;

@RestController(path = "/users")
public class UserController {
	
	@GetMapping
	public List<User> index(
		@Query(name = "name", required = false) String name
	) {
		return IntStream.range(0, 10)
			.mapToObj((x) -> new User())
			.map((user) -> {
				if (name != null) {
					user.setName(name);
				}
				
				return user;
			})
			.toList();
	}
	
	@PostMapping
	public User create(
		@Body UserCreateForm body
	) {
		return new User()
			.setName(body.getName())
			.setAge(body.getAge());
	}
	
	@GetMapping(path = "/:id")
	public User show(
		@Parameter(name = "id") UUID id
	) {
		return new User().setId(id);
	}
	
	@ResponseStatus(HttpStatus.Code.GONE)
	@GetMapping(path = "/x")
	public String indexX() {
		return "hello world x";
	}
	
	@PatchMapping
	public String update() {
		return "cool";
	}
	
	@Data
	@Accessors(chain = true)
	public static class User {
		
		private UUID id = UUID.randomUUID();
		private String name = "Hello";
		private int age;
		
	}
	
	@Data
	@Accessors(chain = true)
	public static class UserCreateForm {
		
		private String name;
		private int age;
		
	}
	
}