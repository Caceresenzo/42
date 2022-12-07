package ft.app.matcha.domain.auth;

import ft.app.matcha.domain.auth.event.LoginEvent;
import ft.app.matcha.domain.auth.event.RefreshEvent;
import ft.app.matcha.domain.auth.event.RegisterEvent;
import ft.app.matcha.domain.auth.exception.InvalidRefreshTokenException;
import ft.app.matcha.domain.auth.exception.WrongLoginOrPasswordException;
import ft.app.matcha.domain.auth.model.LoginForm;
import ft.app.matcha.domain.auth.model.RefreshForm;
import ft.app.matcha.domain.auth.model.RegisterForm;
import ft.app.matcha.domain.auth.model.Tokens;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.framework.event.ApplicationEventPublisher;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class AuthService {
	
	private final UserService userService;
	private final RefreshTokenService refreshTokenService;
	private final JwtService jwtService;
	private final ApplicationEventPublisher eventPublisher;
	
	public Tokens login(LoginForm form) {
		final var password = encode(form.getPassword());
		final var user = userService.find(form.getLogin(), password)
			.orElseThrow(WrongLoginOrPasswordException::new);
		
		eventPublisher.publishEvent(new LoginEvent(this, user));
		
		return createTokens(user);
	}
	
	public Tokens register(RegisterForm form) {
		final var password = encode(form.getPassword());
		final var user = userService.create(form.getLogin(), password);
		
		eventPublisher.publishEvent(new RegisterEvent(this, user));
		
		return createTokens(user);
	}
	
	public Tokens refresh(RefreshForm form) {
		final var refreshToken = refreshTokenService.refresh(form.getRefreshToken())
			.orElseThrow(InvalidRefreshTokenException::new);
		
		eventPublisher.publishEvent(new RefreshEvent(this, refreshToken));
		
		return createTokens(refreshToken);
	}
	
	public Tokens createTokens(User user) {
		return createTokens(refreshTokenService.create(user));
	}
	
	public Tokens createTokens(RefreshToken refreshToken) {
		final var accessToken = jwtService.generate(refreshToken.getUser());
		
		return new Tokens(accessToken, refreshToken.getPlain());
	}
	
	public static String encode(String password) {
		return PasswordEncoder.encode(password);
	}
	
}