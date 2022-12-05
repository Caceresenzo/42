package ft.framework.orm.mapping;

import java.lang.reflect.Field;

import org.apache.commons.lang3.reflect.FieldUtils;

import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.framework.orm.mapping.naming.Named;
import lombok.Builder;
import lombok.Data;
import lombok.SneakyThrows;
import lombok.experimental.SuperBuilder;

@Data
@SuperBuilder
public class Column implements Named {
	
	private final String name;
	private final DataType dataType;
	private final @JsonIgnore Field field;
	private final @Builder.Default boolean nullable = true;
	
	@SneakyThrows
	public Object read(Object instance) {
		return FieldUtils.readField(field, instance, true);
	}

	@SneakyThrows
	public void write(Object instance, Object value) {
		FieldUtils.writeField(field, instance, value, true);
	}

	public boolean isMatching(String name) {
		return this.name.equalsIgnoreCase(name) || field.getName().equalsIgnoreCase(name);
	}
	
}