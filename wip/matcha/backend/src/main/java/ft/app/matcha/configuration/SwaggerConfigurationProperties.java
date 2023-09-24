package ft.app.matcha.configuration;

import javax.validation.constraints.NotBlank;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import lombok.Data;

@Valid
@Data
@ConfigurationProperties(prefix = "swagger")
public class SwaggerConfigurationProperties {
	
	@NotBlank
	private String serverName = "Default";
	
	@NotBlank
	private String serverUrl = "/";
	
}