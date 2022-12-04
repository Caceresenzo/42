package ft.framework.swagger.part;

import java.lang.annotation.Annotation;
import java.util.Arrays;
import java.util.Optional;

import ft.framework.mvc.mapping.Route;
import ft.framework.swagger.annotation.ApiHidden;
import ft.framework.swagger.annotation.ApiOperation;
import io.swagger.models.Operation;
import io.swagger.models.Response;
import spark.utils.StringUtils;

public class OperationBuilder {
	
	public static Optional<Operation> build(Route route) {
		if (route.getMethod().isAnnotationPresent(ApiHidden.class)) {
			return Optional.empty();
		}
		
		final var operation = new Operation();
		
		operation.setOperationId("%s-%s".formatted(route.getMethod().getDeclaringClass().getSimpleName(), route.getMethod().getName()));
		operation.addConsumes(route.getConsume());
		operation.addProduces(route.getProduce());
		operation.setDeprecated(hasAnnotationOrParent(route, Deprecated.class));
		
		final var annotation = route.getMethod().getAnnotation(ApiOperation.class);
		if (annotation != null) {
			final var summary = annotation.summary();
			if (StringUtils.isNotBlank(summary)) {
				operation.setSummary(summary);
			}
			
			final var tags = annotation.tags();
			if (tags.length != 0) {
				operation.setTags(Arrays.asList(tags));
			}
		}
		
		for (final var parameter : route.getParameters()) {
			ParameterBuilder.build(parameter)
				.forEach(operation::addParameter);
		}
		
		final var response = new Response();
		response.setDescription("Default");
		
		PropertyBuilder.build(route.getMethod().getGenericReturnType())
			.ifPresent(response::setSchema);
		
		operation.response(route.getResponseStatus(), response);
		
		return Optional.of(operation);
	}
	
	public static boolean hasAnnotationOrParent(Route route, Class<? extends Annotation> clazz) {
		return route.getMethod().isAnnotationPresent(clazz) || route.getMethod().getDeclaringClass().isAnnotationPresent(clazz);
	}
	
}