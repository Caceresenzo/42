package ft.framework.orm.ddl;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.SQLSyntaxErrorException;
import java.util.ArrayList;
import java.util.List;

import ft.framework.orm.dialect.Dialect;
import ft.framework.orm.error.DuplicateRelationshipException;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.relationship.ManyToOne;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@RequiredArgsConstructor
public class UpdateDDLStrategy implements DDLStrategy {
	
	private final Connection connection;
	private final Dialect dialect;
	
	@Override
	public void apply(List<Entity<?>> entities) {
		final var tablesNames = getTableNames();
		
		for (final var entity : entities) {
			final var table = entity.getTable();
			
			if (tablesNames.contains(table.getName())) {
				alterTable(table);
			} else {
				createTable(table);
			}
		}
		
		for (final var entity : entities) {
			final var table = entity.getTable();
			
			applyConstraints(table);
		}
	}
	
	public void applyConstraints(Table table) {
		final var constraintNames = getConstraintNames(table);
		
		for (final var manyToOne : table.getManyToOnes()) {
			addForeinKey(table, manyToOne);
		}
		
		for (final var index : table.getIndexes()) {
			if (constraintNames.contains(index.getName())) {
				continue;
			}
			
			addIndex(table, index);
		}
		
		for (final var unique : table.getUniques()) {
			if (constraintNames.contains(unique.getName())) {
				continue;
			}
			
			addUnique(table, unique);
		}
	}
	
	public void alterTable(Table table) {
		final var columnNames = getColumnNames(table);
		
		for (final var column : table.getColumns()) {
			if (columnNames.contains(column.getName())) {
				continue;
			}
			
			addColumn(table, column);
		}
	}
	
	@SneakyThrows
	public boolean createTable(Table table) {
		log.info("Creating table `{}`...", table.getName());
		
		final var sql = dialect.buildCreateTableStatement(table);
		return execute(sql);
	}
	
	@SneakyThrows
	public boolean addForeinKey(Table table, ManyToOne manyToOne) {
		// TODO There is no way to list foreign key without using information_schema.
		
		try {
			final var sql = dialect.buildAlterTableAddForeignKeyStatement(table, manyToOne);
			final var result = execute(sql);
			
			log.info("Added forein key `{}` to table `{}`...", manyToOne.getForeignKeyName(), table.getName());
			
			return result;
		} catch (SQLException exception) {
			final var translated = dialect.translate(table, exception);
			
			if (translated instanceof DuplicateRelationshipException relationshipException
				&& manyToOne.equals(relationshipException.getRelationship())) {
				return false;
			}
			
			throw exception;
		}
	}
	
	@SneakyThrows
	public boolean addIndex(Table table, Index index) {
		log.info("Add index `{}` to table `{}`...", index.getName(), table.getName());
		
		final var sql = dialect.buildCreateIndexStatement(table, index);
		return execute(sql);
	}
	
	@SneakyThrows
	public boolean addUnique(Table table, Unique unique) {
		log.info("Add unique `{}` to table `{}`...", unique.getName(), table.getName());
		
		final var sql = dialect.buildAlterTableAddUniqueStatement(table, unique);
		return execute(sql);
	}
	
	@SneakyThrows
	public boolean addColumn(Table table, Column column) {
		log.info("Add column `{}` to table `{}`...", column.getName(), table.getName());
		
		final var sql = dialect.buildAlterTableAddColumnStatement(table, column);
		return execute(sql);
	}
	
	public List<String> getTableNames() {
		final var sql = dialect.buildShowTableStatement();
		return collectColumn(sql, dialect.getTableNameColumnIndex());
	}
	
	public List<String> getColumnNames(Table table) {
		final var sql = dialect.buildShowColumnStatement(table);
		return collectColumn(sql, dialect.getColumnNameColumnIndex());
	}
	
	public List<String> getConstraintNames(Table table) {
		final var sql = dialect.buildShowConstraintStatement(table);
		return collectColumn(sql, dialect.getConstraintNameColumnIndex());
	}
	
	@SneakyThrows
	public List<String> collectColumn(String sql, int index) {
		final var values = new ArrayList<String>();
		
		try (final var statement = connection.createStatement()) {
			try (final var resultSet = statement.executeQuery(sql)) {
				while (resultSet.next()) {
					final var name = resultSet.getString(index);
					
					values.add(name);
				}
			}
		}
		
		return values;
	}
	
	public boolean execute(String sql) throws SQLException {
		try (final var statement = connection.createStatement()) {
			return statement.execute(sql);
		} catch (SQLSyntaxErrorException exception) {
			log.error("SQL: {}", sql);
			throw exception;
		}
	}
	
}