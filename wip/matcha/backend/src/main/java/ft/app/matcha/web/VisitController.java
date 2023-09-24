package ft.app.matcha.web;

import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.domain.visit.VisitService;
import ft.app.matcha.security.UserAuthentication;
import ft.app.matcha.web.dto.VisitDto;
import ft.app.matcha.web.map.VisitMapper;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.security.Authentication;
import ft.framework.swagger.annotation.ApiOperation;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/users/{userId}/visits")
public class VisitController {
	
	private final VisitService visitService;
	private final UserService userService;
	private final VisitMapper visitMapper;
	
	@GetMapping
	@ApiOperation(summary = "List visits.")
	public Page<VisitDto> index(
		@Variable long userId,
		Pageable pageable,
		Authentication authentication
	) {
		final var principal = UserAuthentication.getUser(authentication);
		
		final var user = userService.find(userId)
			.orElseThrow(() -> new UserNotFoundException(userId));
		
		return visitService
			.findAll(user, pageable)
			.map((visit) -> visitMapper.toDto(visit, principal));
	}
	
	@PostMapping
	@ApiOperation(summary = "Create a visits.")
	public void create(
		@Variable long userId,
		Pageable pageable,
		Authentication authentication
	) {
		final var principal = UserAuthentication.getUser(authentication);
		
		final var user = userService.find(userId)
			.orElseThrow(() -> new UserNotFoundException(userId));
		
		visitService.log(user, principal);
	}
	
}