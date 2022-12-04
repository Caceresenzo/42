package ft.framework.swagger.part;

import java.util.Optional;

import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.Variable;
import ft.framework.swagger.annotation.ApiHidden;
import io.swagger.models.parameters.BodyParameter;
import io.swagger.models.parameters.Parameter;
import io.swagger.models.parameters.PathParameter;
import io.swagger.models.parameters.QueryParameter;
import spark.utils.StringUtils;

public class ParameterBuilder {
	
	public static Optional<Parameter> build(java.lang.reflect.Parameter methodParameter) {
		if (methodParameter.isAnnotationPresent(ApiHidden.class)) {
			return Optional.empty();
		}
		
		return callBuilder(methodParameter)
			.map((parameter) -> {
				if (StringUtils.isBlank(parameter.getName())) {
					parameter.setName(methodParameter.getName());
				}
				
				return parameter;
			});
	}
	
	public static Optional<Parameter> callBuilder(java.lang.reflect.Parameter methodParameter) {
		final var variable = methodParameter.getAnnotation(Variable.class);
		if (variable != null) {
			return Optional.of(buildPathParameter(methodParameter, variable));
		}
		
		final var query = methodParameter.getAnnotation(Query.class);
		if (query != null) {
			return Optional.of(buildQueryParameter(methodParameter, query));
		}
		
		final var body = methodParameter.getAnnotation(Body.class);
		if (body != null) {
			return Optional.of(buildBodyParameter(methodParameter, body));
		}
		
		return Optional.empty();
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