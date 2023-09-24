package ft.app.matcha.configuration;

import ft.framework.property.annotation.ConfigurationProperties;
import ft.framework.validation.annotation.Valid;
import ft.framework.validation.constraint.annotation.NotBlank;
import lombok.Data;

@Valid
@Data
@ConfigurationProperties(prefix = "matcha")
public class MatchaConfigurationProperties {
	
	private long maximumPictureCount = 5;
	
	@NotBlank
	private String pictureStorage = "./data/pictures/";
	
	private boolean animatedPictureAllowed = true;
	
	private long maximumTagCount = 5;
	
	private int fameOnLike = 1;
	private int fameOnUnlike = -1;
	private int fameOnBlock = -1;
	private int fameOnReport = -3;
	
	private boolean debug = true;
	
}