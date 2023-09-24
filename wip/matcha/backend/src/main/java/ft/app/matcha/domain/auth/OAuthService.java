package ft.app.matcha.domain.auth;

import java.util.Map;

import org.eclipse.jetty.http.HttpStatus;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import ft.app.matcha.configuration.AuthConfigurationProperties;
import ft.app.matcha.domain.auth.exception.OAuthException;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.JwtException;
import io.jsonwebtoken.Jwts;
import lombok.Getter;
import lombok.SneakyThrows;
import okhttp3.FormBody;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;

public class OAuthService {
	
	public static final String SCOPES = "https://www.googleapis.com/auth/userinfo.email https://www.googleapis.com/auth/userinfo.profile openid";
	public static final HttpUrl TOKEN_URL = HttpUrl.parse("https://oauth2.googleapis.com/token");
	
	private final ObjectMapper objectMapper;
	private final OkHttpClient httpClient;
	private final String clientId;
	private final String clientSecret;
	private final String callbackUrl;
	@Getter
	private final String authorizeUrl;
	
	public OAuthService(ObjectMapper objectMapper, OkHttpClient httpClient, AuthConfigurationProperties properties) {
		this.objectMapper = objectMapper;
		this.httpClient = httpClient;
		this.clientId = properties.getOauthClientId();
		this.clientSecret = properties.getOauthClientSecret();
		this.callbackUrl = properties.getOauthCallbackUrl();
		this.authorizeUrl = buildAuthorizeUrl(properties).toString();
	}
	
	public static HttpUrl buildAuthorizeUrl(AuthConfigurationProperties properties) {
		return HttpUrl
			.parse("https://accounts.google.com/o/oauth2/v2/auth")
			.newBuilder()
			.addEncodedQueryParameter("redirect_uri", properties.getOauthCallbackUrl())
			.addEncodedQueryParameter("prompt", "consent")
			.addEncodedQueryParameter("response_type", "code")
			.addEncodedQueryParameter("client_id", properties.getOauthClientId())
			.addEncodedQueryParameter("scope", SCOPES)
			.build();
	}
	
	@SneakyThrows
	public String getIdToken(String code) {
		final var call = httpClient.newCall(new Request.Builder()
			.url(TOKEN_URL)
			.post(new FormBody.Builder()
				.addEncoded("code", code)
				.addEncoded("redirect_uri", callbackUrl)
				.addEncoded("client_id", clientId)
				.addEncoded("client_secret", clientSecret)
				.addEncoded("scope", SCOPES)
				.addEncoded("grant_type", "authorization_code")
				.build())
			.build());
		
		try (final var response = call.execute()) {
			try (final var body = response.body()) {
				final var string = body.string();
				
				int responseCode = response.code();
				if (responseCode != HttpStatus.OK_200) {
					throw new OAuthException("%s: %s".formatted(responseCode, string));
				}
				
				final var content = objectMapper.readValue(string, new TypeReference<Map<String, Object>>() {});
				return (String) content.get("id_token");
			}
		}
	}
	
	public OAuthUser getUser(String idToken) {
		try {
			final var lastDot = idToken.lastIndexOf('.');
			final var jwt = Jwts.parserBuilder()
				.requireIssuer("https://accounts.google.com")
				.build()
				.parse(idToken.substring(0, lastDot + 1));
			
			final var claims = (Claims) jwt.getBody();
			
			return new OAuthUser(
				(String) claims.get("given_name"),
				(String) claims.get("family_name"),
				(String) claims.get("email"),
				(String) claims.get("picture")
			);
		} catch (JwtException exception) {
			throw new OAuthException("invalid id token", exception);
		}
	}
	
}