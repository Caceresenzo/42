package ft.app.matcha.web;

import ft.app.matcha.domain.auth.AuthService;
import ft.app.matcha.domain.auth.Tokens;
import ft.app.matcha.domain.auth.exception.InvalidConfirmPasswordException;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.security.jwt.JwtCookieAuthenticationFilter;
import ft.app.matcha.web.dto.UserDto;
import ft.app.matcha.web.form.ChangeEmailForm;
import ft.app.matcha.web.form.ChangePasswordForm;
import ft.app.matcha.web.form.ForgotForm;
import ft.app.matcha.web.form.LoginForm;
import ft.app.matcha.web.form.LogoutForm;
import ft.app.matcha.web.form.RefreshForm;
import ft.app.matcha.web.form.RegisterForm;
import ft.app.matcha.web.form.ResetPasswordForm;
import ft.app.matcha.web.form.TokenForm;
import ft.app.matcha.web.map.UserMapper;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.swagger.annotation.ApiOperation;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;
import spark.Request;
import spark.Response;
import spark.utils.StringUtils;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/auth")
public class AuthController {
	
	private final AuthService authService;
	private final UserMapper userMapper;
	
	@GetMapping(path = "/self")
	@Authenticated
	@ApiOperation(summary = "Show authenticated principal.")
	public UserDto self(
		@Principal User principal
	) {
		return userMapper.toDto(principal, principal);
	}
	
	@PostMapping(path = "/login")
	@ApiOperation(summary = "Login with an email and a password.", description = "The tokens will also be added to the cookies.")
	public Tokens login(
		@Body @Valid LoginForm form,
		Response response
	) {
		final var tokens = authService.login(form.getLogin(), form.getPassword());
		
		JwtCookieAuthenticationFilter.addCookiesToResponse(tokens, response);
		
		return tokens;
	}
	
	@PostMapping(path = "/register")
	@ApiOperation(summary = "Create an account.", description = "The tokens will also be added to the cookies.")
	public Tokens register(
		@Body @Valid RegisterForm form,
		Response response
	) {
		final var tokens = authService.register(form.getFirstName(), form.getLastName(), form.getEmail(), form.getLogin(), form.getPassword());
		
		JwtCookieAuthenticationFilter.addCookiesToResponse(tokens, response);
		
		return tokens;
	}
	
	@PostMapping(path = "/refresh")
	@ApiOperation(summary = "Refresh a JWT token using a refresh-token.", description = "This endpoint does not affect the cookies.")
	public Tokens refresh(
		@Body @Valid RefreshForm form,
		Response response
	) {
		return authService.refresh(form.getRefreshToken());
	}
	
	@PostMapping(path = "/logout")
	@ApiOperation(summary = "Logout and invalidate a refresh-token.", description = "If a token is provided in the body, this token will be invalidated, else the one present in the cookies will.")
	public void logout(
		@Body @Valid LogoutForm form,
		Request request,
		Response response
	) {
		var refreshToken = form.getRefreshToken();
		if (StringUtils.isNotBlank(refreshToken)) {
			authService.logout(refreshToken);
			return;
		}
		
		refreshToken = request.cookie(JwtCookieAuthenticationFilter.REFRESH_TOKEN_COOKIE);
		JwtCookieAuthenticationFilter.removeCookiesFromResponse(response);
		
		if (StringUtils.isNotBlank(refreshToken)) {
			authService.logout(refreshToken);
		}
	}
	
	@PostMapping(path = "/confirm-email")
	@ApiOperation(summary = "Confirm an account.")
	public void confirmEmail(
		@Body @Valid TokenForm form
	) {
		authService.confirmEmail(form.getToken());
	}
	
	@PostMapping(path = "/forgot-password")
	@ApiOperation(summary = "Send a 'forgot password' email.")
	public void forgotPassword(
		@Body @Valid ForgotForm form
	) {
		authService.forgotPassword(form.getEmail());
	}
	
	@PostMapping(path = "/change-password")
	@ApiOperation(summary = "Change your password.")
	@Authenticated
	public void changePassword(
		@Body @Valid ChangePasswordForm form,
		@Principal User user
	) {
		if (!form.getNewPassword().equals(form.getConfirmPassword())) {
			throw new InvalidConfirmPasswordException();
		}
		
		authService.changePassword(user, form.getOldPassword(), form.getNewPassword());
	}
	
	@PostMapping(path = "/change-email")
	@ApiOperation(summary = "Change your email.")
	@Authenticated
	public void changeEmail(
		@Body @Valid ChangeEmailForm form,
		@Principal User user
	) {
		authService.changeEmail(user, form.getNewEmail());
	}
	
	@PostMapping(path = "/confirm-new-email")
	@ApiOperation(summary = "Confirm your new email.")
	@Authenticated
	public void confirmNewEmail(
		@Body @Valid TokenForm form,
		@Principal User user
	) {
		authService.confirmNewEmail(form.getToken());
	}
	
	@PostMapping(path = "/reset-password")
	@ApiOperation(summary = "Reset a password with a token provided from a 'forgot password' email.")
	public void resetPassword(
		@Body @Valid ResetPasswordForm form
	) {
		authService.resetPassword(form.getToken(), form.getPassword());
	}
	
	@GetMapping(path = "/oauth/url")
	@ApiOperation(summary = "Get the OAuth's authorize url.")
	public String oauthUrl() {
		return authService.getOAuthUrl();
	}
	
	@GetMapping(path = "/oauth/callback")
	@ApiOperation(summary = "Validate the OAuth's code.")
	public Tokens oauthCallback(
		@Query String code,
		Response response
	) {
		final var tokens = authService.validateOAuthCode(code);
		
		JwtCookieAuthenticationFilter.addCookiesToResponse(tokens, response);
		
		return tokens;
	}
	
}