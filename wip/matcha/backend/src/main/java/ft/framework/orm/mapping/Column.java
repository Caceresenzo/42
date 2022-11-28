package ft.framework.orm.mapping;

import java.lang.reflect.Field;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Builder;
import lombok.Data;
import lombok.experimental.SuperBuilder;

@Data
@SuperBuilder
public class Column {
	
	private final String name;
	private final DataType dataType;
	private final @JsonIgnore Field field;
	private final @Builder.Default boolean nullable = true;
	
}