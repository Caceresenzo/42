package ft.framework.orm;

import lombok.Builder;
import lombok.Data;
import lombok.NonNull;

@Data
@Builder
public class OrmConfiguration {
	
	@NonNull
	private final EntityManager entityManager;
	
}