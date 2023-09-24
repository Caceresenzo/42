package ft.framework.property.resolver;

import java.util.List;
import java.util.Optional;

public interface PropertyResolver {
	
	String getName();
	
	Optional<String> resolve(List<String> paths);
	
}