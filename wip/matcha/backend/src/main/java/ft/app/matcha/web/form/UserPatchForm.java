package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.app.matcha.domain.user.Gender;
import ft.app.matcha.domain.user.SexualOrientation;
import ft.app.matcha.domain.user.User;
import ft.framework.validation.constraint.annotation.Length;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class UserPatchForm {
	
	@Length(min = 1, max = User.LOGIN_MAX_LENGTH)
	private String firstName;
	
	@Length(min = 1, max = User.LOGIN_MAX_LENGTH)
	private String lastName;
	
	@Length(max = User.BIOGRAPHY_MAX_LENGTH)
	private String biography;
	
	private Gender gender;
	
	private SexualOrientation sexualOrientation;
	
}