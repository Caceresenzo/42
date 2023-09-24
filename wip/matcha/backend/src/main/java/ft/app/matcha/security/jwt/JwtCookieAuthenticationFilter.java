package ft.app.matcha.security.jwt;

import java.time.Duration;

import javax.servlet.http.Cookie;

import org.apache.commons.lang3.StringUtils;

import ft.app.matcha.domain.auth.AuthService;
import ft.app.matcha.domain.auth.Tokens;
import ft.app.matcha.domain.auth.exception.InvalidTokenException;
import ft.app.matcha.domain.auth.exception.JwtExpiredException;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.security.UserAuthentication;
import ft.framework.mvc.security.Authentication;
import ft.framework.mvc.security.AuthenticationFilter;
import lombok.RequiredArgsConstructor;
import spark.Request;
import spark.Response;

@RequiredArgsConstructor
public class JwtCookieAuthenticationFilter extends AuthenticationFilter {
	
	public static final String PATH = "/";
	public static final String ACCESS_TOKEN_COOKIE = "auth.accessToken";
	public static final String REFRESH_TOKEN_COOKIE = "auth.refreshToken";
	
	private final JwtAuthenticator jwtAuthenticator;
	private final AuthService authService;
	
	@Override
	public Authentication authenticate(Request request, Response response) {
		final var accessToken = request.cookie(ACCESS_TOKEN_COOKIE);
		final var refreshToken = request.cookie(REFRESH_TOKEN_COOKIE);
		
		try {
			if (StringUtils.isNotBlank(accessToken)) {
				return jwtAuthenticator.authenticate(accessToken);
			}
			
			if (StringUtils.isNotBlank(refreshToken)) {
				final var user = refreshTokens(refreshToken, response);
				if (user != null) {
					return new UserAuthentication(user);
				}
			}
			
			return null;
		} catch (JwtExpiredException exception) {
			final var user = refreshTokens(refreshToken, response);
			if (user != null) {
				return new UserAuthentication(user);
			}
			
			throw exception;
		}
	}
	
	public User refreshTokens(String refreshToken, Response response) {
		try {
			final var tokens = authService.refresh(refreshToken);
			
			addCookiesToResponse(tokens, response);
			
			return tokens.getUser();
		} catch (InvalidTokenException exception) {
			removeCookiesFromResponse(response);
			
			return null;
		}
	}
	
	public static void addCookiesToResponse(Tokens tokens, Response response) {
		final var accessCookie = createCookie(ACCESS_TOKEN_COOKIE, tokens.getAccessToken());
		final var refreshCookie = createCookie(REFRESH_TOKEN_COOKIE, tokens.getRefreshToken());
		
		response.raw().addCookie(accessCookie);
		response.raw().addCookie(refreshCookie);
	}
	
	public static void removeCookiesFromResponse(Response response) {
		response.removeCookie(PATH, ACCESS_TOKEN_COOKIE);
		response.removeCookie(PATH, REFRESH_TOKEN_COOKIE);
	}
	
	public static Cookie createCookie(String name, String value) {
		final var cookie = new Cookie(name, value);
		cookie.setHttpOnly(true);
		cookie.setPath(PATH);
		
		// TODO Use configuration
		cookie.setMaxAge((int) Duration.ofDays(3).getSeconds());
		
		return cookie;
	}
	
}