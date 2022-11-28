package ft.framework.orm.mapping;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class DataType {
	
	private final Class<?> type;
	private final @Builder.Default int length = 255;
	private final @Builder.Default int precision = 2;
	private final @Builder.Default int scale = 16;
	private boolean lotOfByte;
	
}