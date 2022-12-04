package ft.framework.orm.mapping;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Builder;
import lombok.Data;
import lombok.SneakyThrows;

@Data
@Builder
public class Entity {
	
	private final String name;
	private final @JsonIgnore Class<?> clazz;
	private final Table table;
	
	@SneakyThrows
	public Object instantiate() {
		return clazz.getConstructor().newInstance();
	}
	
	@SneakyThrows
	public Object instantiate(Object id) {
		final var instance = instantiate();
		
		table.getIdColumn().write(instance, id);
		
		return instance;
	}
	
}