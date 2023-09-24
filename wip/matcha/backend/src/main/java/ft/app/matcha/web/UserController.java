package ft.app.matcha.web;

import java.util.Optional;

import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.OnlyYourselfException;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.security.UserAuthentication;
import ft.app.matcha.web.dto.UserDto;
import ft.app.matcha.web.form.UserPatchForm;
import ft.app.matcha.web.map.UserMapper;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PatchMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.security.Authentication;
import ft.framework.swagger.annotation.ApiOperation;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/users")
public class UserController {
	
	private final UserService userService;
	private final UserMapper userMapper;
	
	@GetMapping
	@ApiOperation(summary = "List users.")
	public Page<UserDto> index(
		Pageable pageable,
		Authentication authentication
	) {
		final var principal = UserAuthentication.getUser(authentication);
		
		return userService
			.findAll(pageable)
			.map((user) -> userMapper.toDto(user, principal));
	}
	
	@GetMapping(path = "{userId}")
	@ApiOperation(summary = "Show a user.")
	public UserDto show(
		@Variable long userId,
		Authentication authentication
	) {
		final var principal = UserAuthentication.getUser(authentication);
		
		return userService.find(userId)
			.map((user) -> userMapper.toDto(user, principal))
			.orElseThrow(() -> new UserNotFoundException(userId));
	}
	
	@Authenticated
	@PatchMapping(path = "{userId}")
	@ApiOperation(summary = "Update a user.")
	public UserDto patch(
		@Variable long userId,
		@Valid @Body UserPatchForm form,
		@Principal User user
	) {
		if (userId != user.getId()) {
			throw new OnlyYourselfException();
		}
		
		Optional.ofNullable(form.getFirstName()).ifPresent(user::setFirstName);
		Optional.ofNullable(form.getLastName()).ifPresent(user::setLastName);
		Optional.ofNullable(form.getBiography()).ifPresent(user::setBiography);
		Optional.ofNullable(form.getGender()).ifPresent(user::setGender);
		Optional.ofNullable(form.getSexualOrientation()).ifPresent(user::setSexualOrientation);
		
		userService.save(user);
		
		return userMapper.toDto(user);
	}
	
}