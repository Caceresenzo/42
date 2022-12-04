package ft.framework.orm.proxy;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

@JsonIgnoreProperties({ ProxiedEntity.HANDLER_FIELD })
public interface ProxiedEntity {
	
	public static final String HANDLER_FIELD = "$handler";
	
	@JsonIgnore
	EntityHandler getEntityHandler();
	
}