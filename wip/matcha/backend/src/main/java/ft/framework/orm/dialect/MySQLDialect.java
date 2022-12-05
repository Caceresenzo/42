package ft.framework.orm.dialect;

import java.sql.SQLType;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Collection;
import java.util.EnumMap;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import com.mysql.cj.MysqlType;

import ft.framework.mvc.domain.Pageable;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.contraint.Constraint;
import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.naming.Named;
import ft.framework.orm.mapping.relationship.Relationship;
import ft.framework.orm.predicate.Branch;
import ft.framework.orm.predicate.Comparison;
import ft.framework.orm.predicate.Predicate;
import spark.utils.StringUtils;

public class MySQLDialect implements Dialect {
	
	private static final Map<Class<?>, SQLType> simpleTypes = new HashMap<>();
	private static final Map<Branch.Type, String> branchToCode = new EnumMap<>(Branch.Type.class);
	private static final Map<Comparison.Type, String> comparisonToCode = new EnumMap<>(Comparison.Type.class);
	
	static {
		simpleTypes.put(long.class, MysqlType.BIGINT);
		simpleTypes.put(Long.class, MysqlType.BIGINT);
		simpleTypes.put(int.class, MysqlType.INT);
		simpleTypes.put(Integer.class, MysqlType.INT);
		simpleTypes.put(short.class, MysqlType.SMALLINT);
		simpleTypes.put(Short.class, MysqlType.SMALLINT);
		simpleTypes.put(char.class, MysqlType.TINYINT);
		simpleTypes.put(Character.class, MysqlType.TINYINT);
		simpleTypes.put(boolean.class, MysqlType.BIT);
		simpleTypes.put(Boolean.class, MysqlType.TINYINT);
		simpleTypes.put(Boolean.class, MysqlType.TINYINT);
		simpleTypes.put(double.class, MysqlType.DOUBLE);
		simpleTypes.put(Double.class, MysqlType.DOUBLE);
		simpleTypes.put(float.class, MysqlType.DOUBLE);
		simpleTypes.put(Float.class, MysqlType.FLOAT);
		
		simpleTypes.put(LocalDate.class, MysqlType.DATE);
		simpleTypes.put(LocalDateTime.class, MysqlType.DATETIME);
	}
	
	static {
		branchToCode.put(Branch.Type.AND, "AND");
		branchToCode.put(Branch.Type.OR, "OR");
		
		comparisonToCode.put(Comparison.Type.EQUALS, "=");
		comparisonToCode.put(Comparison.Type.NOT_EQUALS, "!=");
		comparisonToCode.put(Comparison.Type.IS, "IS");
		comparisonToCode.put(Comparison.Type.IS_NOT, "IS NOT");
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
	public String buildCreateIndexStatement(Table table, Index index) {
		final var sql = new StringBuilder();
		
		sql.append("CREATE ");
		
		if (index.isUnique()) {
			sql.append("UNIQUE ");
		}
		
		final var name = toName(table, index);
		
		return sql
			.append("INDEX ")
			.append(quote(name))
			.append(' ')
			.append("ON ")
			.append(quote(table))
			.append(quote(index.getColumns(), true))
			.append(";")
			.toString();
	}
	
	@Override
	public String buildAlterTableAddUniqueStatement(Table table, Unique unique) {
		final var sql = new StringBuilder();
		
		final var name = toName(table, unique);
		
		return sql
			.append("ALTER TABLE ")
			.append(quote(table))
			.append(" ADD CONSTRAINT ")
			.append(quote(name))
			.append(" UNIQUE ")
			.append(quote(unique.getColumns(), true))
			.append(';')
			.toString();
	}
	
	@Override
	public String buildInsertStatement(Table table, Collection<Column> columns) {
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
	public String buildUpdateByIdStatement(Table table, Collection<Column> columns) {
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
	public String buildSelectStatement(Table table, Collection<Column> columns) {
		return buildSelectStatement(table, columns, null, null);
	}
	
	@Override
	public String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate) {
		return buildSelectStatement(table, columns, predicate, null);
	}
	
	@Override
	public String buildSelectStatement(Table table, Collection<Column> columns, Predicate<?> predicate, Pageable pageable) {
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
		
		if (predicate != null) {
			sql.append(buildWhere(predicate));
		}
		
		if (pageable != null) {
			sql.append(buildLimitAndOffset(pageable));
		}
		
		sql.append(";");
		
		return sql.toString();
	}
	
	@Override
	public String buildCountStatement(Table table) {
		return buildCountStatement(table, null);
	}
	
	@Override
	public String buildCountStatement(Table table, Predicate<?> predicate) {
		final var sql = new StringBuilder();
		
		sql.append("SELECT ").append("COUNT(*)").append(" FROM `").append(table.getName()).append("`");
		
		if (predicate != null) {
			sql.append(buildWhere(predicate));
		}
		
		sql.append(";");
		
		return sql.toString();
	}
	
	private Object buildLimitAndOffset(Pageable pageable) {
		final var limit = pageable.getSize();
		final var offset = pageable.getPage() * limit;
		
		return " LIMIT %s OFFSET %s".formatted(limit, offset);
	}
	
	public String buildWhere(Predicate<?> predicate) {
		return " WHERE %s".formatted(buildPredicate(predicate));
	}
	
	private String buildPredicate(Predicate<?> predicate) {
		if (predicate instanceof Branch<?> branch) {
			return buildBranch(branch);
		}
		
		if (predicate instanceof Comparison<?> comparison) {
			return buildComparison(comparison);
		}
		
		throw new IllegalArgumentException("unsupported predicate: " + predicate);
	}
	
	private String buildBranch(Branch<?> branch) {
		final var code = branchToCode.get(branch.getType());
		final var withSpace = " %s ".formatted(code);
		
		return branch.getPredicates()
			.stream()
			.map(this::buildPredicate)
			.collect(Collectors.joining(withSpace, "(", ")"));
	}
	
	private String buildComparison(Comparison<?> comparison) {
		final var code = comparisonToCode.get(comparison.getType());
		
		return "`%s` %s ?".formatted(comparison.getColumn().getName(), code);
	}
	
	public String quote(List<? extends Named> nameds, boolean addParentheses) {
		final var quoted = nameds.stream()
			.map(this::quote)
			.collect(Collectors.joining(", "));
		
		if (addParentheses) {
			return "(%s)".formatted(quoted);
		}
		
		return quoted;
	}
	
	public String quote(Named named) {
		return quote(named.getName());
	}
	
	public String quote(String name) {
		return String.format("`%s`", name);
	}
	
	public String toName(Table table, Unique unique) {
		return toName(table, "uk", unique);
	}
	
	public String toName(Table table, Index index) {
		return toName(table, "idx", index);
	}
	
	public String toName(Table table, String type, Constraint constraint) {
		final var name = constraint.getName();
		if (StringUtils.isNotBlank(name)) {
			return name;
		}
		
		final var joined = constraint.getColumns().stream()
			.map(Column::getName)
			.collect(Collectors.joining("-"));
		
		return "%s-%s-%s".formatted(type, table.getName(), joined);
	}
	
}