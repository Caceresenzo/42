package ft.framework.swagger.part;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.resolver.argument.impl.PageableHandlerMethodArgumentResolver;
import ft.framework.swagger.annotation.ApiHidden;
import io.swagger.models.parameters.BodyParameter;
import io.swagger.models.parameters.Parameter;
import io.swagger.models.parameters.PathParameter;
import io.swagger.models.parameters.QueryParameter;
import spark.utils.StringUtils;

public class ParameterBuilder {
	
	public static List<Parameter> build(java.lang.reflect.Parameter methodParameter) {
		if (methodParameter.isAnnotationPresent(ApiHidden.class)) {
			return Collections.emptyList();
		}
		
		return callBuilder(methodParameter)
			.stream()
			.map((parameter) -> {
				if (StringUtils.isBlank(parameter.getName())) {
					parameter.setName(methodParameter.getName());
				}
				
				return parameter;
			})
			.toList();
	}
	
	public static List<Parameter> callBuilder(java.lang.reflect.Parameter methodParameter) {
		final var type = methodParameter.getType();
		if (Pageable.class.equals(type)) {
			return buildPageableParameter();
		}
		
		final var variable = methodParameter.getAnnotation(Variable.class);
		if (variable != null) {
			return Collections.singletonList(buildPathParameter(methodParameter, variable));
		}
		
		final var query = methodParameter.getAnnotation(Query.class);
		if (query != null) {
			return Collections.singletonList(buildQueryParameter(methodParameter, query));
		}
		
		final var body = methodParameter.getAnnotation(Body.class);
		if (body != null) {
			return Collections.singletonList(buildBodyParameter(methodParameter, body));
		}
		
		return Collections.emptyList();
	}
	
	public static List<Parameter> buildPageableParameter() {
		final var size = new QueryParameter();
		size.setName(PageableHandlerMethodArgumentResolver.QUERY_SIZE);
		size.setDefault(PageableHandlerMethodArgumentResolver.DEFAULT_SIZE);
		size.setProperty(PropertyBuilder.build(Long.class).get());
		
		final var page = new QueryParameter();
		page.setName(PageableHandlerMethodArgumentResolver.QUERY_PAGE);
		page.setDefault(PageableHandlerMethodArgumentResolver.DEFAULT_PAGE);
		page.setProperty(PropertyBuilder.build(Long.class).get());
		
		return Arrays.asList(size, page);
	}
	
	public static Parameter buildPathParameter(java.lang.reflect.Parameter methodParameter, Variable annotation) {
		final var parameter = new PathParameter();
		
		final var name = annotation.name();
		if (StringUtils.isNotBlank(name)) {
			parameter.setName(name);
		}
		
		PropertyBuilder.build(methodParameter, methodParameter.getName(), methodParameter.getParameterizedType())
			.ifPresent(parameter::setProperty);
		
		return parameter;
	}
	
	public static Parameter buildQueryParameter(java.lang.reflect.Parameter methodParameter, Query annotation) {
		final var parameter = new QueryParameter();
		
		final var name = annotation.name();
		if (StringUtils.isNotBlank(name)) {
			parameter.setName(name);
		}
		
		PropertyBuilder.build(methodParameter, methodParameter.getName(), methodParameter.getParameterizedType())
			.ifPresent(parameter::setProperty);
		
		return parameter;
	}
	
	public static Parameter buildBodyParameter(java.lang.reflect.Parameter methodParameter, Body annotation) {
		final var parameter = new BodyParameter();
		
		ModelBuilder.build(methodParameter, methodParameter.getName(), methodParameter.getParameterizedType())
			.ifPresent(parameter::schema);
		
		return parameter;
	}
	
}