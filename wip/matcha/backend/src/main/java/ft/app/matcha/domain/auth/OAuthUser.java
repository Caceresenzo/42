package ft.app.matcha.domain.auth;

public record OAuthUser(
	String firstName,
	String lastName,
	String email,
	String pictureUrl) {
	
}