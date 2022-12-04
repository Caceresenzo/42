package ft.framework.orm.mapping;

import java.util.ArrayList;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.framework.orm.mapping.relationship.ManyToOne;
import lombok.Builder;
import lombok.Data;
import lombok.Singular;

@Data
@Builder
public class Table {
	
	private final String name;
	private final Column idColumn;
	private final @Singular List<Column> columns;
	private final @Singular List<ManyToOne> manyToOnes;
	
	@JsonIgnore
	public List<Column> getAllColumns() {
		final var list = new ArrayList<Column>();
		
		list.addAll(columns);
		list.addAll(manyToOnes);
		
		return list;
	}
	
	@JsonIgnore
	public List<Column> getAllColumnsWithoutId() {
		final var list = getAllColumns();
		
		if (!list.remove(idColumn)) {
			throw new IllegalStateException("id column was not removed");
		}
		
		return list;
	}
	
}