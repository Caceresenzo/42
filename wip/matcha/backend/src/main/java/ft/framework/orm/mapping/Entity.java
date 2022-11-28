package ft.framework.orm.mapping;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class Entity {
	
	private final String name;
	private final @JsonIgnore Class<?> clazz;
	private final Table table;
	
}