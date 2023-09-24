package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.app.matcha.domain.user.User;
import ft.framework.validation.constraint.annotation.Email;
import ft.framework.validation.constraint.annotation.Length;
import ft.framework.validation.constraint.annotation.NotBlank;
import ft.framework.validation.constraint.annotation.NotNull;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class RegisterForm {
	
	@NotNull
	@Length(min = 1, max = User.LOGIN_MAX_LENGTH)
	private String firstName;
	
	@NotNull
	@Length(min = 1, max = User.LOGIN_MAX_LENGTH)
	private String lastName;
	
	@NotBlank
	@Length(min = User.LOGIN_MIN_LENGTH, max = User.LOGIN_MAX_LENGTH)
	private String login;
	
	@NotBlank
	private String password;
	
	@NotBlank
	@Email
	@Length(max = User.EMAIL_MAX_LENGTH)
	private String email;
	
}