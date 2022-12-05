package ft.framework.swagger.part;

import java.lang.annotation.Annotation;
import java.lang.reflect.Parameter;
import java.util.Collections;
import java.util.Optional;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.mapping.Route;
import ft.framework.swagger.annotation.ApiHidden;
import ft.framework.swagger.annotation.ApiOperation;
import io.swagger.v3.oas.models.OpenAPI;
import io.swagger.v3.oas.models.Operation;
import io.swagger.v3.oas.models.media.Content;
import io.swagger.v3.oas.models.media.MediaType;
import io.swagger.v3.oas.models.parameters.RequestBody;
import io.swagger.v3.oas.models.responses.ApiResponse;
import io.swagger.v3.oas.models.responses.ApiResponses;
import io.swagger.v3.oas.models.security.SecurityRequirement;
import spark.utils.StringUtils;

public class OperationBuilder {
	
	public static Optional<Operation> build(OpenAPI swagger, Route route) {
		if (route.getMethod().isAnnotationPresent(ApiHidden.class)) {
			return Optional.empty();
		}
		
		final var operation = new Operation();
		
		operation.setOperationId("%s-%s".formatted(route.getMethod().getDeclaringClass().getSimpleName(), route.getMethod().getName()));
		operation.setDeprecated(hasAnnotationOrParent(route, Deprecated.class));
		
		final var annotation = route.getMethod().getAnnotation(ApiOperation.class);
		if (annotation != null) {
			final var summary = annotation.summary();
			if (StringUtils.isNotBlank(summary)) {
				operation.setSummary(summary);
			}
		}
		
		for (final var parameter : route.getParameters()) {
			ParameterBuilder.build(swagger, parameter)
				.forEach(operation::addParametersItem);
		}
		
		for (final var parameter : route.getParameters()) {
			if (parameter.isAnnotationPresent(Body.class)) {
				operation.requestBody(buildRequestBody(swagger, route, parameter));
				break;
			}
		}
		
		if (route.isAuthenticated()) {
			final var securitySchemes = swagger.getComponents().getSecuritySchemes();
			
			if (!securitySchemes.isEmpty()) {
				final var first = securitySchemes.keySet().iterator().next();
				
				operation.addSecurityItem(new SecurityRequirement()
					.addList(first, Collections.emptyList()));
			}
		}
		
		final var responses = new ApiResponses();
		operation.responses(responses);
		
		responses.addApiResponse(String.valueOf(route.getResponseStatus()), buildDefaultResponse(swagger, route));
		
		TagBuilder.build(swagger, route)
			.ifPresent((tag) -> operation.tags(Collections.singletonList(tag.getName())));
		
		return Optional.of(operation);
	}
	
	public static boolean hasAnnotationOrParent(Route route, Class<? extends Annotation> clazz) {
		return route.getMethod().isAnnotationPresent(clazz) || route.getMethod().getDeclaringClass().isAnnotationPresent(clazz);
	}
	
	public static ApiResponse buildDefaultResponse(OpenAPI swagger, Route route) {
		final var mediaType = new MediaType();
		SchemaBuilder.build(swagger, route.getMethod().getGenericReturnType())
			.ifPresent(mediaType::schema);
		
		final var content = new Content();
		content.addMediaType(route.getProduce(), mediaType);
		
		final var response = new ApiResponse();
		response.setDescription("Default");
		response.setContent(content);
		
		return response;
	}
	
	public static RequestBody buildRequestBody(OpenAPI swagger, Route route, Parameter parameter) {
		final var mediaType = new MediaType();
		SchemaBuilder.build(swagger, parameter.getParameterizedType())
			.ifPresent(mediaType::setSchema);
		
		final var content = new Content();
		content.addMediaType(route.getConsume(), mediaType);
		
		final var requestBody = new RequestBody();
		requestBody.content(content);
		
		return requestBody;
	}
	
}