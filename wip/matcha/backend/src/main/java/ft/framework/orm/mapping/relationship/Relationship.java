package ft.framework.orm.mapping.relationship;

import ft.framework.orm.mapping.Entity;
import ft.framework.orm.mapping.naming.Named;

public interface Relationship extends Named {
	
	String getForeignKeyName();
	
	Entity<?> getTarget();
	
}