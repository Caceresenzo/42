package ft.app.matcha.configuration;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.annotation.Email;
import ft.framework.validation.constraint.annotation.NotBlank;
import ft.framework.validation.constraint.annotation.Port;
import lombok.Data;
import lombok.ToString;

@Valid
@Data
@ConfigurationProperties(prefix = "mail")
public class EmailConfigurationProperties {
	
	private String defaultSubject = "A message from matcha";
	
	@NotBlank
	private String host = "smtp.gmail.com";
	
	@Port
	private int port = 465;
	
	private boolean auth = true;
	private boolean ssl = true;
	private boolean debug = true;
	
	@Email
	private String authEmail;
	
	@ToString.Exclude
	private String authPassword;

	private String sender = "system@matcha.caceresenzo.dev";
	
}