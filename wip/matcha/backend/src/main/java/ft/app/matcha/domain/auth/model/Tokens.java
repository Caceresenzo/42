package ft.app.matcha.domain.auth.model;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Tokens {
	
	public String accessToken;
	public String refreshToken;
	
}