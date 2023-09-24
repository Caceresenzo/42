package ft.app.matcha.web.dto;

import java.time.LocalDate;
import java.time.LocalTime;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonPropertyDescription;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class VisitDto {
	
	private long id;
	
	@JsonPropertyDescription("aka the viewer")
	private UserDto user;
	
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDate date;
	
	private long times;
	
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalTime firstAt;
	
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalTime lastAt;
	
}