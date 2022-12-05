package ft.framework.swagger;

import java.util.Comparator;
import java.util.List;
import java.util.TreeMap;

import ft.framework.mvc.mapping.Route;
import ft.framework.swagger.part.OperationBuilder;
import io.swagger.v3.oas.models.Components;
import io.swagger.v3.oas.models.OpenAPI;
import io.swagger.v3.oas.models.PathItem;
import io.swagger.v3.oas.models.PathItem.HttpMethod;
import io.swagger.v3.oas.models.Paths;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class SwaggerBuilder {
	
	public static OpenAPI build(OpenAPI swagger, List<Route> routes) {
		swagger.setPaths(new Paths());
		
		if (swagger.getComponents() == null) {
			swagger.setComponents(new Components());
		}
		
		swagger.getComponents()
			.schemas(new TreeMap<>(Comparator.naturalOrder()));
		
		routes.stream()
			.sorted()
			.forEach((route) -> {
				final var operation = OperationBuilder.build(swagger, route);
				
				if (operation.isPresent()) {
					final var path = swagger.getPaths().computeIfAbsent(route.getPath(), (key) -> new PathItem());
					final var method = convert(route.getHttpMethod());
					
					path.operation(method, operation.get());
				}
				
			});
		
		return swagger;
	}
	
	public static HttpMethod convert(spark.route.HttpMethod method) {
		return HttpMethod.valueOf(method.name().toUpperCase());
	}
	
}