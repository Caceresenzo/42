package ft.app.matcha.domain.auth.model;

import ft.app.matcha.domain.user.User;
import ft.framework.validation.constraint.annotation.Length;
import ft.framework.validation.constraint.annotation.NotBlank;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class RegisterForm {
	
	@NotBlank
	@Length(min = User.LOGIN_MIN_LENGTH, max = User.LOGIN_MAX_LENGTH)
	private String login;
	
	@NotBlank
	private String password;
	
}