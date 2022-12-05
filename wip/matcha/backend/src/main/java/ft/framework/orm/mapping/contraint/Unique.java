package ft.framework.orm.mapping.contraint;

import java.util.List;

import ft.framework.orm.mapping.Column;
import lombok.Builder;
import lombok.Data;
import lombok.Singular;

@Data
@Builder
public class Unique implements Constraint {
	
	private final String name;
	
	@Singular
	private final List<Column> columns;
	
	@Override
	public boolean isUnique() {
		return true;
	}
	
}