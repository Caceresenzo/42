package ft.app.matcha.web.dto;

import com.fasterxml.jackson.annotation.JsonInclude;

import ft.app.matcha.domain.heartbeat.Presence;
import ft.app.matcha.domain.user.Gender;
import ft.app.matcha.domain.user.SexualOrientation;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class UserDto {
	
	private long id;
	private String login;
	
	@JsonInclude(JsonInclude.Include.NON_NULL)
	private String email;
	
	private String firstName;
	private String lastName;
	private String biography;
	private Gender gender;
	private SexualOrientation sexualOrientation;
	private long fame;
	private boolean emailConfirmed;

	private PictureDto picture;
	private RelationshipDto relationship;
	private LocationDto location;
	private Presence presence;
	
}