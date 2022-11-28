package ft.framework.orm.mapping.relationship;

import ft.framework.orm.mapping.Column;
import ft.framework.orm.mapping.Entity;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.ToString;
import lombok.experimental.SuperBuilder;

@Data
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
@SuperBuilder
public class ManyToOne extends Column implements Relationship {
	
	private final Entity target;
	
}