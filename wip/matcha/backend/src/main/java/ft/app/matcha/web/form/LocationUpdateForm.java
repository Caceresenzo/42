package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.framework.validation.constraint.annotation.NotNull;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class LocationUpdateForm {
	
	@NotNull
	private Double latitude;

	@NotNull
	private Double longitude;
	
}