package ft.framework.mvc.resolver.argument.impl;

import java.lang.reflect.Parameter;
import java.util.Arrays;
import java.util.Collections;
import java.util.Optional;
import java.util.TreeMap;
import java.util.function.Function;
import java.util.function.Predicate;

import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.domain.Sort;
import ft.framework.mvc.domain.Sort.Order;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import ft.framework.validation.Validator;
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
	public static final String QUERY_SORT = "sort";
	
	private final Validator validator;
	
	@Override
	public boolean supportsParameter(Parameter method) {
		return Pageable.class.equals(method.getType());
	}
	
	@Override
	public Object resolveArgument(Parameter parameter, Request request, Response response) throws Exception {
		final var page = getOrDefault(request, QUERY_PAGE, DEFAULT_PAGE);
		final var size = getOrDefault(request, QUERY_SIZE, DEFAULT_SIZE);
		final var sort = parseSort(request);
		
		final var pageable = new Pageable(size, page, sort);
		
		return validator.validateOrThrow(pageable);
	}
	
	public long getOrDefault(Request request, String query, long defaultValue) {
		final var value = request.queryParams(query);
		
		if (StringUtils.isNotBlank(value)) {
			return Long.parseLong(value);
		}
		
		return defaultValue;
	}
	
	public Sort parseSort(Request request) {
		final var items = request.queryParamsValues(QUERY_SORT);
		
		if (items == null || items.length == 0) {
			return Sort.UNSORTED;
		}
		
		final var orders = Arrays.asList(items)
			.stream()
			.map(this::parseSort)
			.filter(Optional::isPresent)
			.map(Optional::get)
			.filter(distinctByKey(Order::getProperty))
			.toList();
		
		return new Sort(orders);
	}
	
	public Optional<Sort.Order> parseSort(String item) {
		final var part = item.split(",", 2);
		
		final var property = part[0].trim();
		if (StringUtils.isBlank(property)) {
			return Optional.empty();
		}
		
		final var builder = Sort.Order.builder()
			.property(property);
		
		if (part.length == 2) {
			Sort.Direction.parse(part[1])
				.ifPresent(builder::direction);
		}
		
		return Optional.of(builder.build());
	}
	
	public static <T> Predicate<T> distinctByKey(Function<? super T, String> keyExtractor) {
		final var seen = Collections.synchronizedSortedMap(new TreeMap<String, Boolean>(String.CASE_INSENSITIVE_ORDER));
		return t -> seen.putIfAbsent(keyExtractor.apply(t), Boolean.TRUE) == null;
	}
	
}