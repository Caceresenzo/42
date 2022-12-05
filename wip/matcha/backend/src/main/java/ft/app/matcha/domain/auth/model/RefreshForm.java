package ft.app.matcha.domain.auth.model;

import ft.framework.validation.constraint.annotation.NotBlank;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class RefreshForm {
	
	@NotBlank
	private String refreshToken;
	
}