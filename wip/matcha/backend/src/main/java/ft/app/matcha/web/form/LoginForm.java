package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.framework.validation.constraint.annotation.NotBlank;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class LoginForm {
	
	@NotBlank
	private String login;
	
	@NotBlank
	private String password;
	
}