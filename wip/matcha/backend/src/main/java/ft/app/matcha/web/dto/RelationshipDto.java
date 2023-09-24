package ft.app.matcha.web.dto;

import java.time.LocalDateTime;

import com.fasterxml.jackson.annotation.JsonFormat;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@NoArgsConstructor
@AllArgsConstructor
public class RelationshipDto {
	
	private Type type;
	private boolean mutual;
	
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime createdAt;
	
	public enum Type {
		
		LIKE,
		BLOCK,
		STRANGER,
		YOURSELF;
	
	}
	
}