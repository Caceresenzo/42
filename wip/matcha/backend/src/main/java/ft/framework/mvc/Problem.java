package ft.framework.mvc;

import java.util.List;
import java.util.Map;

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
	
	@JsonInclude(JsonInclude.Include.NON_EMPTY)
	private final Map<String, Object> properties;
	
	@JsonInclude(JsonInclude.Include.NON_NULL)
	private final List<String> trace;
	
}