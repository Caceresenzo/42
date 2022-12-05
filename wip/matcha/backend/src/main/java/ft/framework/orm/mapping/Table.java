package ft.framework.orm.mapping;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.naming.Named;
import ft.framework.orm.mapping.relationship.ManyToOne;
import lombok.Builder;
import lombok.Data;
import lombok.Singular;

@Data
@Builder
public class Table implements Named {
	
	private final String name;
	private final Column idColumn;
	private final @Singular List<Column> columns;
	private final @Singular List<ManyToOne> manyToOnes;
	private final @Singular("index") List<Index> indexes;
	private final @Singular List<Unique> uniques;
	
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
	
	public int getColumnCount() {
		return columns.size() + manyToOnes.size();
	}
	
	// TODO Use lookup table
	public Column getColumnByFieldName(String name) {
		var column = getColumnByFieldName(name, columns);
		if (column != null) {
			return column;
		}
		
		column = getColumnByFieldName(name, manyToOnes);
		if (column != null) {
			return column;
		}
		
		throw new NoSuchElementException("no column with field name: " + name);
	}
	
	private static Column getColumnByFieldName(String name, List<? extends Column> columns) {
		for (final var column : columns) {
			if (column.getField().getName().equals(name)) {
				return column;
			}
		}
		
		return null;
	}
	
}