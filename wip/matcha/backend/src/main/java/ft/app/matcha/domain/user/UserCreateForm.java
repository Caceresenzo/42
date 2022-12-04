package ft.app.matcha.domain.user;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class UserCreateForm {
	
	private String name;
	private String bio;
	
}