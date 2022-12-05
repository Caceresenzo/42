package ft.framework.orm.dialect;

import java.util.Collection;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.relationship.Relationship;
import ft.framework.orm.predicate.Predicate;

public interface Dialect {
	
	public String translate(DataType dataType);
	
	public String buildCreateTableStatement(Table table);
	
	public String buildAlterTableAddForeignKeyStatement(Table table, Relationship relationship);

	public String buildInsertStatement(Table table, Collection<Column> columns);
	
	public String buildUpdateByIdStatement(Table table, Collection<Column> columns);
	
	public String buildSelectByIdStatement(Table table, Collection<Column> columns);
	
	public String buildSelectStatement(Table table, Collection<Column> columns);
	
	public String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate);
	
}