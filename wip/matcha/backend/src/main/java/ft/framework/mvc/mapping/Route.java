package ft.framework.mvc.mapping;

import java.lang.reflect.Method;
import java.lang.reflect.Parameter;
import java.util.Arrays;
import java.util.List;

import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import spark.route.HttpMethod;

@Data
@Builder
public class Route {
	
	private final String path;
	private final HttpMethod httpMethod;
	private final Object container;
	private final Method method;
	private final String consume;
	private final String produce;
	private final boolean authenticated;
	
	@Getter(lazy = true)
	private final List<Parameter> parameters = Arrays.asList(method.getParameters());
	
}