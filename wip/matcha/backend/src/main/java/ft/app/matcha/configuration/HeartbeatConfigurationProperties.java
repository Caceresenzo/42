package ft.app.matcha.configuration;

import java.time.Duration;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.annotation.NotBlank;
import lombok.Data;

@Valid
@Data
@ConfigurationProperties(prefix = "heartbeat")
public class HeartbeatConfigurationProperties {
	
	private Duration availabilityTimeout = Duration.ofMinutes(5);
	
	private String maxmindLicenseKey;
	
	@NotBlank
	private String maxmindGeoIpDatabasePath = "./data/geoip.mmdb";
	
}