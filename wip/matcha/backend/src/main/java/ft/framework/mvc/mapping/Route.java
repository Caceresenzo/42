package ft.framework.mvc.mapping;

import java.lang.reflect.Method;
import java.lang.reflect.Parameter;
import java.util.Arrays;
import java.util.List;

import org.eclipse.jetty.http.HttpStatus;

import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import lombok.NonNull;
import spark.route.HttpMethod;

@Data
@Builder
public class Route implements Comparable<Route> {
	
	@NonNull
	private final String path;
	
	@NonNull
	private final HttpMethod httpMethod;
	
	@NonNull
	private final Object container;
	
	@NonNull
	private final Method method;
	
	@NonNull
	private final String consume;
	
	@NonNull
	private final String produce;
	
	@Builder.Default
	private final boolean authenticated = false;
	
	@Builder.Default
	private final int responseStatus = HttpStatus.OK_200;
	
	@Builder.Default
	private final boolean responseBody = false;
	
	@Getter(lazy = true)
	private final List<Parameter> parameters = Arrays.asList(method.getParameters());
	
	@Override
	public int compareTo(Route other) {
		return path.compareTo(other.path);
	}
	
}