package ft.framework.orm.error;

import java.sql.SQLException;

import ft.framework.orm.mapping.contraint.Constraint;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
public class DuplicateValueException extends RuntimeException {
	
	private final String value;
	private final Constraint constraint;
	
	public DuplicateValueException(String value, Constraint constraint, SQLException cause) {
		super(cause);
		
		this.value = value;
		this.constraint = constraint;
	}
	
}