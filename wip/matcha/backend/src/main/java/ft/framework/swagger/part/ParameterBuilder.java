package ft.framework.swagger.part;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.resolver.argument.impl.PageableHandlerMethodArgumentResolver;
import ft.framework.swagger.annotation.ApiHidden;
import io.swagger.v3.oas.models.OpenAPI;
import io.swagger.v3.oas.models.parameters.Parameter;
import io.swagger.v3.oas.models.parameters.PathParameter;
import io.swagger.v3.oas.models.parameters.QueryParameter;
import spark.utils.StringUtils;

public class ParameterBuilder {
	
	public static List<Parameter> build(OpenAPI swagger, java.lang.reflect.Parameter methodParameter) {
		if (methodParameter.isAnnotationPresent(ApiHidden.class)) {
			return Collections.emptyList();
		}
		
		return callBuilder(swagger, methodParameter)
			.stream()
			.map((parameter) -> {
				if (StringUtils.isBlank(parameter.getName())) {
					parameter.setName(methodParameter.getName());
				}
				
				return parameter;
			})
			.toList();
	}
	
	public static List<Parameter> callBuilder(OpenAPI swagger, java.lang.reflect.Parameter methodParameter) {
		final var type = methodParameter.getType();
		if (Pageable.class.equals(type)) {
			return buildPageableParameter(swagger);
		}
		
		final var variable = methodParameter.getAnnotation(Variable.class);
		if (variable != null) {
			return Collections.singletonList(buildPathParameter(swagger, methodParameter, variable));
		}
		
		final var query = methodParameter.getAnnotation(Query.class);
		if (query != null) {
			return Collections.singletonList(buildQueryParameter(swagger, methodParameter, query));
		}
		
		return Collections.emptyList();
	}
	
	public static List<Parameter> buildPageableParameter(OpenAPI swagger) {
		final var size = new QueryParameter();
		{
			final var schema = SchemaBuilder.build(swagger, Long.class).get();
			schema.setDefault(PageableHandlerMethodArgumentResolver.DEFAULT_SIZE);
			
			size.setName(PageableHandlerMethodArgumentResolver.QUERY_SIZE);
			size.setSchema(schema);
		}
		
		final var page = new QueryParameter();
		{
			final var schema = SchemaBuilder.build(swagger, Long.class).get();
			schema.setDefault(PageableHandlerMethodArgumentResolver.DEFAULT_PAGE);
			
			page.setName(PageableHandlerMethodArgumentResolver.QUERY_PAGE);
			page.setSchema(schema);
		}
		
		return Arrays.asList(size, page);
	}
	
	public static Parameter buildPathParameter(OpenAPI swagger, java.lang.reflect.Parameter methodParameter, Variable annotation) {
		final var parameter = new PathParameter();
		
		final var name = annotation.name();
		if (StringUtils.isNotBlank(name)) {
			parameter.setName(name);
		}
		
		SchemaBuilder.build(swagger, methodParameter.getParameterizedType())
			.ifPresent(parameter::setSchema);
		
		return parameter;
	}
	
	public static Parameter buildQueryParameter(OpenAPI swagger, java.lang.reflect.Parameter methodParameter, Query annotation) {
		final var parameter = new QueryParameter();
		
		final var name = annotation.name();
		if (StringUtils.isNotBlank(name)) {
			parameter.setName(name);
		}
		
		SchemaBuilder.build(swagger, methodParameter.getParameterizedType())
			.ifPresent(parameter::setSchema);
		
		return parameter;
	}
	
}