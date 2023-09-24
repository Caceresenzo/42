package ft.framework.orm.error;

import java.sql.SQLException;

import ft.framework.orm.mapping.relationship.Relationship;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
public class DuplicateRelationshipException extends RuntimeException {
	
	private final Relationship relationship;
	
	public DuplicateRelationshipException(Relationship relationship, SQLException cause) {
		super(cause);
		
		this.relationship = relationship;
	}
	
}