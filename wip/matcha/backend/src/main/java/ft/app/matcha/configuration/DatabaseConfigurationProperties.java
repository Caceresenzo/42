package ft.app.matcha.configuration;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.annotation.NotBlank;
import ft.framework.validation.constraint.annotation.Port;
import lombok.Data;
import lombok.ToString;

@Valid
@Data
@ConfigurationProperties(prefix = "database")
public class DatabaseConfigurationProperties {
	
	@NotBlank
	private String host = "localhost";
	
	@Port
	private int port = 3306;
	
	private String user;
	
	@ToString.Exclude
	private String password;

	@NotBlank
	private String database = "matcha";

	@NotBlank
	private boolean autoReconnect = true;
	
}