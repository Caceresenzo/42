package ft.app.matcha.web;

import ft.app.matcha.domain.location.LocationService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.OnlyYourselfException;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.web.dto.LocationDto;
import ft.app.matcha.web.form.LocationUpdateForm;
import ft.app.matcha.web.map.LocationMapper;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.DeleteMapping;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Variable;
import ft.framework.swagger.annotation.ApiOperation;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;

@Controller
@RequestMapping(path = "/users/{userId}/location")
@RequiredArgsConstructor
public class LocationController {
	
	private final LocationService locationService;
	private final UserService userService;
	private final LocationMapper locationMapper;
	
	@GetMapping
	@ApiOperation(summary = "Get a user's location.")
	public LocationDto show(
		@Variable long userId
	) {
		final var user = userService.find(userId)
			.orElseThrow(() -> new UserNotFoundException(userId));
		
		final var location = locationService.find(user);
		return locationMapper.toDto(location);
	}
	
	@Authenticated
	@PostMapping
	@ApiOperation(summary = "Update a user's location.")
	public LocationDto create(
		@Variable long userId,
		@Body @Valid LocationUpdateForm form,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var location = locationService.update(user, form.getLatitude(), form.getLongitude());
		return locationMapper.toDto(location);
	}
	
	@Authenticated
	@DeleteMapping
	@ApiOperation(summary = "Delete a user's location.")
	public LocationDto delete(
		@Variable long userId,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var location = locationService.delete(user);
		return locationMapper.toDto(location);
	}
	
	public void ensureSelf(long userId, User currentUser) {
		if (userId != currentUser.getId()) {
			throw new OnlyYourselfException();
		}
	}
	
}