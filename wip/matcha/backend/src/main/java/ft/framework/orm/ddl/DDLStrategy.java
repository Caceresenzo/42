package ft.framework.orm.ddl;

import java.util.List;

import ft.framework.orm.mapping.Entity;

public interface DDLStrategy {
	
	void apply(List<Entity<?>> entities);
	
}