package ft.app.matcha.dto;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class UserCreateForm {
	
	private String name;
	private String bio;
	
}