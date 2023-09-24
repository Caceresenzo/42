package ft.framework.orm.dialect;

import java.sql.SQLException;
import java.util.Collection;

import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.relationship.ManyToOne;
import ft.framework.orm.predicate.Predicate;

public interface Dialect {
	
	Exception translate(Table table, SQLException exception);
	
	String translate(DataType dataType);
	
	String buildCreateTableStatement(Table table);
	
	String buildAlterTableAddColumnStatement(Table table, Column column);
	
	String buildAlterTableAddForeignKeyStatement(Table table, ManyToOne relationship);
	
	String buildCreateIndexStatement(Table table, Index index);
	
	String buildAlterTableAddUniqueStatement(Table table, Unique unique);
	
	String buildInsertStatement(Table table, Collection<Column> columns);
	
	Object buildDeleteStatement(Table table, Predicate<?> predicate);
	
	String buildUpdateByIdStatement(Table table, Collection<Column> columns);
	
	String buildDeleteByIdStatement(Table table);
	
	String buildSelectByIdStatement(Table table, Collection<Column> columns);
	
	String buildSelectStatement(Table table, Collection<Column> columns);
	
	String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate);
	
	String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate, Pageable pageable);
	
	String buildCountStatement(Table table);
	
	String buildCountStatement(Table table, Predicate<?> predicate);

	Object buildExistsStatement(Table table, Predicate<?> predicate);
	
	String buildShowTableStatement();
	
	String buildShowColumnStatement(Table table);
	
	String buildShowConstraintStatement(Table table);
	
	default int getTableNameColumnIndex() {
		return 1;
	}
	
	default int getColumnNameColumnIndex() {
		return 1;
	}
	
	default int getConstraintNameColumnIndex() {
		return 1;
	}
	
}