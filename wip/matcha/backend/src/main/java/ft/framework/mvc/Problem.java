package ft.framework.mvc;

import java.util.Map;

import com.fasterxml.jackson.annotation.JsonAnyGetter;
import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonInclude;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class Problem {
	
	@JsonInclude(JsonInclude.Include.NON_NULL)
	private final String type;
	
	@JsonInclude(JsonInclude.Include.NON_NULL)
	private final String title;
	
	@JsonInclude(JsonInclude.Include.NON_NULL)
	private final Integer status;
	
	@JsonInclude(JsonInclude.Include.NON_NULL)
	private final String detail;
	
	@JsonIgnore
	private final Map<String, Object> properties;
	
	@JsonAnyGetter
	public Map<String, Object> getProperties() {
		return properties;
	}
	
}