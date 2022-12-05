package ft.app.matcha.domain.auth;

import ft.app.matcha.domain.auth.model.LoginForm;
import ft.app.matcha.domain.auth.model.RefreshForm;
import ft.app.matcha.domain.auth.model.RegisterForm;
import ft.app.matcha.domain.auth.model.Tokens;
import ft.app.matcha.domain.user.User;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/auth")
public class AuthController {
	
	private final AuthService authService;
	
	@GetMapping(path = "/self")
	@Authenticated
	public User self(
		@Principal User principal
	) {
		return principal;
	}
	
	@PostMapping(path = "/login")
	public Tokens login(
		@Body @Valid LoginForm form
	) {
		return authService.login(form);
	}
	
	@PostMapping(path = "/register")
	public Tokens register(
		@Body @Valid RegisterForm form
	) {
		return authService.register(form);
	}
	
	@PostMapping(path = "/refresh")
	public Tokens refresh(
		@Body @Valid RefreshForm form
	) {
		return authService.refresh(form);
	}
	
}