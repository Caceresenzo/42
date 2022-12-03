package ft.framework.mvc;

import java.util.List;

import com.fasterxml.jackson.databind.ObjectMapper;

import ft.framework.convert.service.ConvertionService;
import ft.framework.convert.service.SimpleConvertionService;
import ft.framework.mvc.filter.Filter;
import ft.framework.mvc.http.convert.HttpMessageConversionService;
import ft.framework.mvc.resolver.argument.HandlerMethodArgumentResolver;
import ft.framework.mvc.resolver.exception.DefaultHandlerExceptionResolver;
import ft.framework.mvc.resolver.exception.HandlerExceptionResolver;
import ft.framework.validation.Validator;
import lombok.Builder;
import lombok.Getter;
import lombok.NonNull;
import lombok.Singular;

@Builder
@Getter
public class MvcConfiguration {
	
	@NonNull
	@Builder.Default
	private final ObjectMapper objectMapper = new ObjectMapper();
	
	@NonNull
	private final HttpMessageConversionService httpMessageConversionService;
	
	@NonNull
	@Builder.Default
	private final ConvertionService conversionService = new SimpleConvertionService();
	
	@NonNull
	@Builder.Default
	private Validator validator = new Validator();
	
	@NonNull
	@Singular
	private List<HandlerMethodArgumentResolver> methodArgumentResolvers;
	
	@NonNull
	@Builder.Default
	private HandlerExceptionResolver exceptionResolver = new DefaultHandlerExceptionResolver();
	
	@Singular
	private final List<Filter> filters;
	
}