package ft.app.matcha.configuration;

import java.time.Duration;

import org.apache.commons.lang3.RandomStringUtils;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import lombok.Data;

@Valid
@Data
@ConfigurationProperties(prefix = "auth")
public class AuthConfigurationProperties {
	
	private String jwtSecret = RandomStringUtils.randomAlphanumeric(128);
	private Duration jwtExpiration = Duration.ofMinutes(15);
	
	private int refreshTokenLength = 128;
	private Duration refreshTokenExpiration = Duration.ofDays(7);
	
	private int confirmEmailTokenLength = 128;
	private Duration confirmEmailTokenExpiration = Duration.ofDays(1);
	
	private int passwordTokenLength = 128;
	private Duration passwordTokenExpiration = Duration.ofHours(1);
	
	private int newEmailTokenLength = 128;
	private Duration newEmailTokenExpiration = Duration.ofHours(1);
	
	private String oauthClientId;
	private String oauthClientSecret;
	private String oauthCallbackUrl;
	
}