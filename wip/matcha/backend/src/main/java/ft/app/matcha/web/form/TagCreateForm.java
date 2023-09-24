package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.app.matcha.domain.tag.Tag;
import ft.framework.validation.constraint.annotation.Length;
import ft.framework.validation.constraint.annotation.NotBlank;
import ft.framework.validation.constraint.annotation.NotEmpty;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class TagCreateForm {
	
	@NotBlank
	@Length(max = Tag.MAX_NAME_LENGTH)
	private String name;
	
	@NotEmpty
	@Length(max = Tag.MAX_COLOR_LENGTH)
	private String color;
	
}