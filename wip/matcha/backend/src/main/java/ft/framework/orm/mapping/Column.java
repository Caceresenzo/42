package ft.framework.orm.mapping;

import java.lang.reflect.Field;
import java.time.LocalDate;
import java.time.LocalTime;

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
		if (instance == null) {
			return null;
		}
		
		var value = FieldUtils.readField(field, instance, true);

		// TODO This should be moved
		if (value != null && isEnum()) {
			value = ((Enum<?>) value).name();
		}
		
		return value;
	}
	
	@SuppressWarnings("unchecked")
	@SneakyThrows
	public void write(Object instance, Object value) {
		// TODO This should be moved
		if (value != null && isEnum()) {
			value = Enum.<Fake>valueOf((Class<Fake>) dataType.getType(), (String) value);
		}

		// TODO This should be moved
		if (value instanceof java.sql.Date date && field.getType().equals(LocalDate.class)) {
			value = date.toLocalDate();
		}

		// TODO This should be moved
		if (value instanceof java.sql.Time time && field.getType().equals(LocalTime.class)) {
			value = time.toLocalTime();
		}
		
		FieldUtils.writeField(field, instance, value, true);
	}
	
	public boolean isMatching(String name) {
		return this.name.equalsIgnoreCase(name) || field.getName().equalsIgnoreCase(name);
	}
	
	public boolean isEnum() {
		return dataType.getType().isEnum();
	}
	
	private enum Fake {};
	
}