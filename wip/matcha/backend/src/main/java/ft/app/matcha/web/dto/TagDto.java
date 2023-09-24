package ft.app.matcha.web.dto;

import java.time.LocalDateTime;

import com.fasterxml.jackson.annotation.JsonFormat;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class TagDto {
	
	private long id;
	private String name;
	private String color;
	private long usage;
	
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime createdAt;
	
}