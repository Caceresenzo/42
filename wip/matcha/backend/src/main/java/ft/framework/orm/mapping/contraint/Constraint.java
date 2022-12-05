package ft.framework.orm.mapping.contraint;

import java.util.List;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.naming.Named;

public interface Constraint extends Named {
	
	List<Column> getColumns();
	
	boolean isUnique();
	
}