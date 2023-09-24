package ft.app.matcha.configuration;

import javax.validation.constraints.NotBlank;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import lombok.Data;

@Valid
@Data
@ConfigurationProperties(prefix = "url")
public class UrlConfigurationProperties {
	
	private String base = "http://localhost:3000";
	
	@NotBlank
	private String confirmEmail = "{base}/auth/confirm-email?token={token}";
	
	@NotBlank
	private String changePassword = "{base}/auth/change-password?token={token}";
	
	@NotBlank
	private String changeEmail = "{base}/auth/change-email?token={token}";
	
}