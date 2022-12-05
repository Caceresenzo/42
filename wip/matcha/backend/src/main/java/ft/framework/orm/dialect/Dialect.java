package ft.framework.orm.dialect;

import java.util.Collection;

import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.relationship.Relationship;
import ft.framework.orm.predicate.Predicate;

public interface Dialect {
	
	public String translate(DataType dataType);
	
	public String buildCreateTableStatement(Table table);
	
	public String buildAlterTableAddForeignKeyStatement(Table table, Relationship relationship);
	
	public String buildCreateIndexStatement(Table table, Index index);
	
	public String buildAlterTableAddUniqueStatement(Table table, Unique unique);
	
	public String buildInsertStatement(Table table, Collection<Column> columns);
	
	public Object buildDeleteStatement(Table table, Predicate<?> predicate);
	
	public String buildUpdateByIdStatement(Table table, Collection<Column> columns);
	
	public String buildDeleteByIdStatement(Table table);
	
	public String buildSelectStatement(Table table, Collection<Column> columns);
	
	public String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate);
	
	public String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate, Pageable pageable);
	
	public String buildCountStatement(Table table);
	
	public String buildCountStatement(Table table, Predicate<?> predicate);
	
}