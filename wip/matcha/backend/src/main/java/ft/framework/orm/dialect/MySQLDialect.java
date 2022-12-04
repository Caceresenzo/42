package ft.framework.orm.dialect;

import java.sql.SQLType;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.mysql.cj.MysqlType;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.relationship.Relationship;

public class MySQLDialect implements Dialect {
	
	private final Map<Class<?>, SQLType> simpleTypes;
	
	public MySQLDialect() {
		this.simpleTypes = createSimpleTypesMapping();
	}
	
	@Override
	public String translate(DataType dataType) {
		final var type = dataType.getType();
		
		final var simpleType = simpleTypes.get(type);
		if (simpleType != null) {
			return simpleType.getName();
		}
		
		if (String.class.equals(type)) {
			final var length = dataType.getLength();
			var sqlType = MysqlType.LONGTEXT;
			
			if (!dataType.isLotOfByte()) {
				if (length <= MysqlType.VARCHAR.getPrecision()) {
					sqlType = MysqlType.VARCHAR;
				} else if (length <= MysqlType.MEDIUMTEXT.getPrecision()) {
					sqlType = MysqlType.MEDIUMTEXT;
				} else if (length <= MysqlType.TEXT.getPrecision()) {
					sqlType = MysqlType.TEXT;
				}
			}
			
			if (MysqlType.VARCHAR.equals(sqlType)) {
				return String.format("%s(%s)", sqlType.getName(), length);
			} else {
				return sqlType.getName();
			}
		}
		
		// TODO Decimal
		
		throw new IllegalArgumentException("could not translate: " + dataType);
	}
	
	@Override
	public String buildCreateTableStatement(Table table) {
		final var sql = new StringBuilder();
		
		sql.append("CREATE TABLE `").append(table.getName()).append("`(\n");
		
		for (final var column : table.getAllColumns()) {
			sql.append("\t`").append(column.getName()).append("` ").append(translate(column.getDataType()));
			
			if (!column.isNullable()) {
				sql.append(" NOT NULL");
			}
			
			if (table.getIdColumn().equals(column)) {
				sql.append(" AUTO_INCREMENT");
			}
			
			sql.append(",\n");
		}
		
		sql.append("\tPRIMARY KEY(`" + table.getIdColumn().getName() + "`)\n");
		sql.append(");");
		
		return sql.toString();
	}
	
	@Override
	public String buildAlterTableAddForeignKeyStatement(Table table, Relationship relationship) {
		final var sql = new StringBuilder();
		
		final var targetTable = relationship.getTarget().getTable();
		final var idColumn = table.getIdColumn();
		
		sql.append("ALTER TABLE `").append(table.getName()).append("` ");
		
		final var keyName = "fk-%s-%s".formatted(table.getName(), relationship.getName());
		
		sql.append("ADD CONSTRAINT `").append(keyName).append("` FOREIGN KEY (`").append(relationship.getName()).append("`)")
			.append(" REFERENCES `").append(targetTable.getName()).append("`(`").append(idColumn.getName()).append("`);");
		
		return sql.toString();
	}
	
	@Override
	public String buildInsertStatement(Table table, List<Column> columns) {
		final var sql = new StringBuilder();
		
		sql.append("INSERT INTO `").append(table.getName()).append("`(");
		
		final var iterator = columns.iterator();
		while (iterator.hasNext()) {
			final var column = iterator.next();
			
			sql.append("`").append(column.getName()).append("`");
			
			if (iterator.hasNext()) {
				sql.append(", ");
			}
		}
		
		sql.append(") VALUES (");
		
		final var columnCount = columns.size();
		for (int index = 0; index < columnCount; ++index) {
			sql.append("?");
			
			if (index != columnCount - 1) {
				sql.append(", ");
			}
		}
		
		sql.append(");");
		
		return sql.toString();
	}
	
	@Override
	public String buildUpdateByIdStatement(Table table, List<Column> columns) {
		final var sql = new StringBuilder();
		
		sql.append("UPDATE `").append(table.getName()).append("` SET ");
		
		final var iterator = columns.iterator();
		while (iterator.hasNext()) {
			final var column = iterator.next();
			
			sql.append("`").append(column.getName()).append("` = ?");
			
			if (iterator.hasNext()) {
				sql.append(", ");
			}
		}
		
		sql.append(" WHERE `").append(table.getIdColumn().getName()).append("` = ?");
		
		return sql.toString();
	}
	
	@Override
	public String buildSelectByIdStatement(Table table, List<Column> columns) {
		return buildIncompleteSelectStatement(table, columns)
			.append(" WHERE `").append(table.getIdColumn().getName()).append("` = ?")
			.append(";")
			.toString();
	}
	
	@Override
	public String buildSelectStatement(Table table, List<Column> columns) {
		return buildIncompleteSelectStatement(table, columns)
			.append(";")
			.toString();
	}
	
	private StringBuilder buildIncompleteSelectStatement(Table table, List<Column> columns) {
		final var sql = new StringBuilder();
		
		sql.append("SELECT ");
		
		final var iterator = columns.iterator();
		while (iterator.hasNext()) {
			final var column = iterator.next();
			
			sql.append("`").append(column.getName()).append("`");
			
			if (iterator.hasNext()) {
				sql.append(", ");
			}
		}
		
		sql.append(" FROM `").append(table.getName()).append("`");
		
		return sql;
	}
	
	public static Map<Class<?>, SQLType> createSimpleTypesMapping() {
		final var mapping = new HashMap<Class<?>, SQLType>();
		
		mapping.put(long.class, MysqlType.BIGINT);
		mapping.put(Long.class, MysqlType.BIGINT);
		mapping.put(int.class, MysqlType.INT);
		mapping.put(Integer.class, MysqlType.INT);
		mapping.put(short.class, MysqlType.SMALLINT);
		mapping.put(Short.class, MysqlType.SMALLINT);
		mapping.put(char.class, MysqlType.TINYINT);
		mapping.put(Character.class, MysqlType.TINYINT);
		mapping.put(boolean.class, MysqlType.BIT);
		mapping.put(Boolean.class, MysqlType.TINYINT);
		mapping.put(Boolean.class, MysqlType.TINYINT);
		mapping.put(double.class, MysqlType.DOUBLE);
		mapping.put(Double.class, MysqlType.DOUBLE);
		mapping.put(float.class, MysqlType.DOUBLE);
		mapping.put(Float.class, MysqlType.FLOAT);
		
		mapping.put(LocalDate.class, MysqlType.DATE);
		mapping.put(LocalDateTime.class, MysqlType.DATETIME);
		
		return mapping;
	}
	
}