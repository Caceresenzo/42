package ft.framework.orm.dialect;

import java.sql.SQLException;
import java.sql.SQLType;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.EnumMap;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

import com.mysql.cj.MysqlType;

import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.domain.Sort;
import ft.framework.orm.annotation.OnDelete;
import ft.framework.orm.error.DuplicateRelationshipException;
import ft.framework.orm.error.DuplicateValueException;
import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.DataType;
import ft.framework.orm.mapping.Table;
import ft.framework.orm.mapping.contraint.Constraint;
import ft.framework.orm.mapping.contraint.Index;
import ft.framework.orm.mapping.contraint.Unique;
import ft.framework.orm.mapping.naming.Named;
import ft.framework.orm.mapping.relationship.ManyToOne;
import ft.framework.orm.mapping.relationship.Relationship;
import ft.framework.orm.predicate.Branch;
import ft.framework.orm.predicate.Comparison;
import ft.framework.orm.predicate.Predicate;

public class MySQLDialect implements Dialect {
	
	public static final Pattern DUPLICATE_VALUE_PATTERN = Pattern.compile("^Duplicate entry '(.*?)' for key '(.*?)'$");
	public static final Pattern DUPLICATE_FOREIGN_KEY_PATTERN = Pattern.compile("^Duplicate foreign key constraint name '(.*?)'$");
	
	private static final Map<Class<?>, SQLType> simpleTypes = new HashMap<>();
	private static final Map<Branch.Type, String> branchToCode = new EnumMap<>(Branch.Type.class);
	private static final Map<Comparison.Type, String> comparisonToCode = new EnumMap<>(Comparison.Type.class);
	private static final Map<Sort.Direction, String> sortDirectionToCode = new EnumMap<>(Sort.Direction.class);
	private static final Map<OnDelete.Action, String> onDeleteActionToCode = new EnumMap<>(OnDelete.Action.class);
	
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
		simpleTypes.put(LocalTime.class, MysqlType.TIME);
		
		branchToCode.put(Branch.Type.AND, "AND");
		branchToCode.put(Branch.Type.OR, "OR");
		
		comparisonToCode.put(Comparison.Type.EQUALS, "=");
		comparisonToCode.put(Comparison.Type.NOT_EQUALS, "!=");
		comparisonToCode.put(Comparison.Type.IS, "IS");
		comparisonToCode.put(Comparison.Type.IS_NOT, "IS NOT");
		comparisonToCode.put(Comparison.Type.LESS_THAN, "<");
		comparisonToCode.put(Comparison.Type.LESS_THAN_EQUALS, "<=");
		comparisonToCode.put(Comparison.Type.GREATER_THAN, ">");
		comparisonToCode.put(Comparison.Type.GREATER_THAN_EQUALS, ">=");
		comparisonToCode.put(Comparison.Type.LIKE, "LIKE");
		
		sortDirectionToCode.put(Sort.Direction.ASCENDING, "ASC");
		sortDirectionToCode.put(Sort.Direction.DESCENDING, "DESC");
		
		onDeleteActionToCode.put(OnDelete.Action.RESTRICT, "RESTRICT");
		onDeleteActionToCode.put(OnDelete.Action.SET_NULL, "SET_NULL");
		onDeleteActionToCode.put(OnDelete.Action.NO_ACTION, "NO_ACTION");
		onDeleteActionToCode.put(OnDelete.Action.CASCADE, "CASCADE");
	}
	
	@Override
	public Exception translate(Table table, SQLException exception) {
		final var message = exception.getMessage();
		
		var matcher = DUPLICATE_VALUE_PATTERN.matcher(message);
		if (matcher.find()) {
			final var value = matcher.group(1);
			
			var constraintName = matcher.group(2);
			final var lastDotIndex = constraintName.lastIndexOf('.');
			if (lastDotIndex != -1) {
				constraintName = constraintName.substring(lastDotIndex + 1);
			}
			
			System.out.println(constraintName);
			final var constraint = findConstraintByName(table, constraintName);
			
			return new DuplicateValueException(value, constraint, exception);
		}
		
		matcher = DUPLICATE_FOREIGN_KEY_PATTERN.matcher(message);
		if (matcher.find()) {
			final var relationship = findRelationByName(table, matcher.group(1));
			
			return new DuplicateRelationshipException(relationship, exception);
		}
		
		return exception;
	}
	
	private Relationship findRelationByName(Table table, String name) {
		for (final var manyToOne : table.getManyToOnes()) {
			if (manyToOne.getForeignKeyName().equalsIgnoreCase(name)) {
				return manyToOne;
			}
		}
		
		return null;
	}
	
	private Constraint findConstraintByName(Table table, String name) {
		final var index = findNamed(table.getIndexes(), name);
		if (index != null) {
			return index;
		}
		
		final var unique = findNamed(table.getUniques(), name);
		if (unique != null) {
			return unique;
		}
		
		return null;
	}
	
	public <T extends Named> T findNamed(List<T> list, String name) {
		for (final var named : list) {
			if (named.getName().equalsIgnoreCase(name)) {
				return named;
			}
		}
		
		return null;
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
				return "%s(%s)".formatted(sqlType.getName(), length);
			} else {
				return sqlType.getName();
			}
		}
		
		if (type.isEnum()) {
			final var constants = Arrays.stream(type.getEnumConstants())
				.map(Enum.class::cast)
				.map(Enum::name)
				.map((name) -> "'%s'".formatted(name))
				.collect(Collectors.joining(", "));
			
			return "%s(%s)".formatted(MysqlType.ENUM.getName(), constants);
		}
		
		// TODO Decimal
		
		throw new IllegalArgumentException("could not translate: " + dataType);
	}
	
	@Override
	public String buildCreateTableStatement(Table table) {
		final var sql = new StringBuilder()
			.append("CREATE TABLE ")
			.append(quote(table)).append("(\n");
		
		for (final var column : table.getColumns()) {
			boolean isId = table.getIdColumn().equals(column);
			
			sql.append("\t")
				.append(buildColumn(column, isId))
				.append(",\n");
		}
		
		return sql
			.append("\tPRIMARY KEY(").append(quote(table.getIdColumn())).append(")\n")
			.append(");")
			.toString();
	}
	
	public String buildColumn(Column column, boolean isId) {
		final var sql = new StringBuilder()
			.append(quote(column))
			.append(' ')
			.append(translate(column.getDataType()));
		
		if (!column.isNullable()) {
			sql.append(" NOT NULL");
		}
		
		if (isId) {
			sql.append(" AUTO_INCREMENT");
		}
		
		return sql.toString();
	}
	
	@Override
	public String buildAlterTableAddColumnStatement(Table table, Column column) {
		return new StringBuilder()
			.append("ALTER TABLE ")
			.append(quote(table))
			.append(" ADD ")
			.append(buildColumn(column, false))
			.toString();
	}
	
	@Override
	public String buildAlterTableAddForeignKeyStatement(Table table, ManyToOne relationship) {
		final var targetTable = relationship.getTarget().getTable();
		final var idColumn = table.getIdColumn();
		
		final var keyName = "fk-%s-%s".formatted(table.getName(), relationship.getName());
		
		final var sql = new StringBuilder()
			.append("ALTER TABLE ")
			.append(quote(table))
			.append(" ADD CONSTRAINT ")
			.append(quote(keyName))
			.append(" FOREIGN KEY ")
			.append(paranthesis(quote(relationship)))
			.append(" REFERENCES ")
			.append(quote(targetTable))
			.append(paranthesis(quote(idColumn)));
		
		final var onDeleteAction = relationship.getOnDeleteAction();
		if (onDeleteAction != null) {
			sql
				.append(" ON DELETE ")
				.append(onDeleteActionToCode.get(onDeleteAction));
		}
		
		return sql
			.append(";")
			.toString();
	}
	
	@Override
	public String buildCreateIndexStatement(Table table, Index index) {
		final var sql = new StringBuilder();
		
		sql.append("CREATE ");
		
		if (index.isUnique()) {
			sql.append("UNIQUE ");
		}
		
		return sql
			.append("INDEX ")
			.append(quote(index))
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
		
		return sql
			.append("ALTER TABLE ")
			.append(quote(table))
			.append(" ADD CONSTRAINT ")
			.append(quote(unique))
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
	public Object buildDeleteStatement(Table table, Predicate<?> predicate) {
		return new StringBuilder()
			.append("DELETE FROM ")
			.append(quote(table))
			.append(buildWhere(predicate))
			.append(';')
			.toString();
	}
	
	@Override
	public String buildDeleteByIdStatement(Table table) {
		return new StringBuilder()
			.append("DELETE FROM ")
			.append(quote(table))
			.append(" WHERE ")
			.append(quote(table.getIdColumn()))
			.append(" = ?")
			.append(';')
			.toString();
	}
	
	@Override
	public String buildSelectByIdStatement(Table table, Collection<Column> columns) {
		return buildSelectFrom(table, columns)
			.append(buildWhereId(table))
			.toString();
	}
	
	private String buildWhereId(Table table) {
		return new StringBuilder()
			.append(" WHERE ")
			.append(quote(table.getIdColumn()))
			.append(" = ?;")
			.toString();
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
		return buildSelectFrom(table, columns)
			.append(buildWhere(predicate))
			.append(buildPageable(table, pageable))
			.append(";")
			.toString();
	}
	
	@Override
	public String buildCountStatement(Table table) {
		return buildCountStatement(table, null);
	}
	
	@Override
	public String buildCountStatement(Table table, Predicate<?> predicate) {
		return new StringBuilder()
			.append("SELECT COUNT(*) FROM ")
			.append(quote(table))
			.append(buildWhere(predicate))
			.append(";")
			.toString();
	}
	
	@Override
	public Object buildExistsStatement(Table table, Predicate<?> predicate) {
		return new StringBuilder()
			.append("SELECT 1 FROM ")
			.append(quote(table))
			.append(buildWhere(predicate))
			.append(";")
			.toString();
	}
	
	@Override
	public String buildShowTableStatement() {
		return "SHOW TABLES;";
	}
	
	@Override
	public String buildShowColumnStatement(Table table) {
		return new StringBuilder()
			.append("SHOW COLUMNS FROM ")
			.append(quote(table))
			.append(';')
			.toString();
	}
	
	@Override
	public String buildShowConstraintStatement(Table table) {
		return new StringBuilder()
			.append("SHOW KEYS FROM ")
			.append(quote(table))
			.append(';')
			.toString();
	}
	
	@Override
	public int getConstraintNameColumnIndex() {
		return 3;
	}
	
	public StringBuilder buildSelectFrom(Table table, Collection<Column> columns) {
		return new StringBuilder()
			.append("SELECT ")
			.append(quote(columns, false))
			.append(" FROM ")
			.append(quote(table));
	}
	
	public String buildPageable(Table table, Pageable pageable) {
		return new StringBuilder()
			.append(buildOrderBy(table, pageable != null ? pageable.getSort() : null))
			.append(buildLimitAndOffset(pageable))
			.toString();
	}
	
	public String buildOrderBy(Table table, Sort sort) {
		if (sort == null) {
			return "";
		}
		
		final var orders = sort.getOrders();
		if (orders.isEmpty()) {
			return "";
		}
		
		final var pairs = new ArrayList<Map.Entry<Column, Sort.Direction>>(orders.size());
		
		for (final var order : orders) {
			final var column = table.findColumnByFieldName(order.getProperty());
			
			if (column == null) {
				continue;
			}
			
			pairs.add(Map.entry(column, order.getDirection()));
		}
		
		if (pairs.isEmpty()) {
			return "";
		}
		
		return new StringBuilder()
			.append(" ORDER BY ")
			.append(pairs.stream().map(this::buildSort).collect(Collectors.joining(", ")))
			.toString();
	}
	
	public String buildSort(Map.Entry<Column, Sort.Direction> entry) {
		final var column = entry.getKey();
		final var direction = entry.getValue();
		
		return new StringBuilder()
			.append(quote(column))
			.append(" ")
			.append(sortDirectionToCode.get(direction))
			.toString();
	}
	
	public Object buildLimitAndOffset(Pageable pageable) {
		if (pageable == null) {
			return "";
		}
		
		final var limit = pageable.getSize();
		final var offset = pageable.getPage() * limit;
		
		return " LIMIT %s OFFSET %s".formatted(limit, offset);
	}
	
	public String buildWhere(Predicate<?> predicate) {
		if (predicate == null) {
			return "";
		}
		
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
	
	public String quote(Collection<? extends Named> nameds, boolean addParentheses) {
		final var quoted = nameds.stream()
			.map(this::quote)
			.collect(Collectors.joining(", "));
		
		if (addParentheses) {
			return paranthesis(quoted);
		}
		
		return quoted;
	}
	
	public String quote(Named named) {
		return quote(named.getName());
	}
	
	public String quote(String name) {
		return "`%s`".formatted(name);
	}
	
	public String paranthesis(String code) {
		return "(%s)".formatted(code);
	}
	
}