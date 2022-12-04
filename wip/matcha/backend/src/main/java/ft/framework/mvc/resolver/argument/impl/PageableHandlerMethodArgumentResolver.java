package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;

import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import lombok.RequiredArgsConstructor;
import spark.Request;
import spark.Response;
import spark.utils.StringUtils;

@RequiredArgsConstructor
public class PageableHandlerMethodArgumentResolver implements HandlerMethodArgumentResolver {
	
	public static final long DEFAULT_SIZE = 20;
	public static final long DEFAULT_PAGE = 0;
	public static final String QUERY_PAGE = "page";
	public static final String QUERY_SIZE = "size";
	
	@Override
	public boolean supportsParameter(Parameter method) {
		return Pageable.class.equals(method.getType());
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var page = getOrDefault(request, QUERY_PAGE, DEFAULT_PAGE);
		final var size = getOrDefault(request, QUERY_SIZE, DEFAULT_SIZE);
		
		return new Pageable(size, page);
	}
	
	public long getOrDefault(Request request, String query, long defaultValue) {
		final var value = request.queryParams(query);
		
		if (StringUtils.isNotBlank(value)) {
			return Long.parseLong(value);
		}
		
		return defaultValue;
	}
	
}