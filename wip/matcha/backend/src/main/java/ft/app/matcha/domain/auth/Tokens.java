package ft.app.matcha.domain.auth;

import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.app.matcha.domain.user.User;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Tokens {
	
	@JsonIgnore
	private User user;
	
	private String accessToken;
	private String refreshToken;
	
}