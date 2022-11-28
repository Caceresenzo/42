package ft.framework.orm.dialect;

import java.util.List;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.relationship.Relationship;

public interface Dialect {
	
	public String translate(DataType dataType);
	
	public String buildCreateTableStatement(Table table);
	
	public String buildAlterTableAddForeignKeyStatement(Table table, Relationship relationship);

	public String buildInsertStatement(Table table, List<Column> columns);
	
}