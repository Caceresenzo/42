package ft.framework.orm.mapping.relationship;

import ft.framework.orm.mapping.Entity;

public interface Relationship {
	
	String getName();
	
	Entity getTarget();
	
}