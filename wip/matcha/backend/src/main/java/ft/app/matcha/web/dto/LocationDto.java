package ft.app.matcha.web.dto;

import java.time.LocalDateTime;

import com.fasterxml.jackson.annotation.JsonFormat;

import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
public class LocationDto {
	
	private boolean shared;
	private Double latitude;
	private Double longitude;
	
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime updatedAt;
	
}