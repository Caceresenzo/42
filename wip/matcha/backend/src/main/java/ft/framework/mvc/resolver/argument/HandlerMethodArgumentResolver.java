package ft.framework.mvc.resolver.argument;

import java.lang.reflect.Parameter;

import spark.Request;
import spark.Response;

public interface HandlerMethodArgumentResolver {

	boolean supportsParameter(Parameter parameter);

	Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception;

}