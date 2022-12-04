package ft.framework.swagger;

import java.util.HashMap;
import java.util.List;

import ft.framework.mvc.mapping.Route;
import ft.framework.swagger.part.OperationBuilder;
import io.swagger.models.Path;
import io.swagger.models.Swagger;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class SwaggerBuilder {
	
	public static Swagger build(Swagger swagger, List<Route> routes) {
		final var paths = new HashMap<String, Path>();
		swagger.setPaths(paths);
		
		for (final var route : routes) {
			final var operation = OperationBuilder.build(route);
			
			if (operation.isPresent()) {
				final var path = paths.computeIfAbsent(route.getPath(), (key) -> new Path());
				path.set(route.getHttpMethod().name().toLowerCase(), operation.get());
			}
		}
		
		return swagger;
	}
	
}