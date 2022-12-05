package ft.framework.orm.mapping.contraint;

import java.util.List;

import ft.framework.orm.mapping.Column;
import lombok.Builder;
import lombok.Data;
import lombok.Singular;

@Data
@Builder
public class Index implements Constraint {
	
	private final String name;
	
	@Singular
	private final List<Column> columns;
	
	private final boolean unique;
	
}