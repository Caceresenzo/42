package ft.app.matcha.domain.auth;

import ft.app.matcha.domain.auth.exception.InvalidRefreshTokenException;
import ft.app.matcha.domain.auth.exception.WrongLoginOrPasswordException;
import ft.app.matcha.domain.auth.model.LoginForm;
import ft.app.matcha.domain.auth.model.RefreshForm;
import ft.app.matcha.domain.auth.model.RegisterForm;
import ft.app.matcha.domain.auth.model.Tokens;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class AuthService {
	
	private final UserService userService;
	private final RefreshTokenService refreshTokenService;
	private final JwtService jwtService;
	
	public Tokens login(LoginForm form) {
		final var password = encode(form.getPassword());
		final var user = userService.find(form.getLogin(), password);
		
		return user
			.map(this::createTokens)
			.orElseThrow(WrongLoginOrPasswordException::new);
	}
	
	public Tokens register(RegisterForm form) {
		final var password = encode(form.getPassword());
		final var user = userService.create(form.getLogin(), password);
		
		return createTokens(user);
	}
	
	public Tokens refresh(RefreshForm form) {
		final var refreshToken = refreshTokenService.refresh(form.getRefreshToken());
		
		return refreshToken.map(this::createTokens)
			.orElseThrow(InvalidRefreshTokenException::new);
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