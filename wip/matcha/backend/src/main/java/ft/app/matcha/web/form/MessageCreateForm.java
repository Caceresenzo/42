package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.app.matcha.domain.message.Message;
import ft.framework.validation.constraint.annotation.Length;
import ft.framework.validation.constraint.annotation.NotBlank;
import ft.framework.validation.constraint.annotation.NotNull;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class MessageCreateForm {
	
	@NotBlank
	@Length(max = Message.MAX_CONTENT_LENGTH)
	private String content;
	
	@NotNull
	private Long peerId;
	
}