package ft.framework.mvc.resolver.exception;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.stream.Collectors;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.exception.ExceptionUtils;
import org.apache.commons.lang3.reflect.FieldUtils;
import org.apache.commons.lang3.reflect.MethodUtils;

import ft.framework.mvc.Problem;
import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.SneakyThrows;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class DefaultHandlerExceptionResolver implements HandlerExceptionResolver {
	
	private boolean debug;
	
	@Override
	public Problem resolveException(HttpServletRequest request, HttpServletResponse response, Exception exception) {
		final var builder = Problem.builder();
		
		final var type = formatType(exception.getClass());
		builder.type(type);
		
		final var message = exception.getMessage();
		if (StringUtils.isNotEmpty(message)) {
			builder.title(message);
		}
		
		final var status = resolveStatus(exception.getClass());
		if (status != null) {
			builder.status(status);
		}
		
		final var properties = resolveProperties(exception);
		if (!properties.isEmpty()) {
			builder.properties(properties);
		}
		
		if (debug) {
			final var trace = resolveTrace(exception);
			if (!properties.isEmpty()) {
				builder.trace(trace);
			}
		}
		
		return builder.build();
	}
	
	public static List<String> resolveTrace(Exception exception) {
		return Arrays.asList(ExceptionUtils.getStackTrace(exception).split("\n"));
	}
	
	private static final List<Class<?>> IGNORED_CLASSES = Arrays.asList(Exception.class, Throwable.class);
	
	public static String formatType(Class<?> clazz) {
		final var parts = StringUtils.splitByCharacterTypeCamelCase(clazz.getSimpleName());
		
		if (!IGNORED_CLASSES.contains(clazz)) {
			final int lastIndex = parts.length - 1;
			if (parts.length > 1 && "Exception".equals(parts[lastIndex])) {
				parts[lastIndex] = null;
			}
		}
		
		return Arrays.stream(parts)
			.filter(Objects::nonNull)
			.map(String::toUpperCase)
			.collect(Collectors.joining("_"));
	}
	
	public static Integer resolveStatus(Class<?> clazz) {
		final var annotation = clazz.getAnnotation(ResponseStatus.class);
		if (annotation == null) {
			return null;
		}
		
		return annotation.value();
	}
	
	@SneakyThrows
	public static Map<String, Object> resolveProperties(Object object) {
		final var extras = new HashMap<String, Object>();
		
		for (final var field : FieldUtils.getAllFields(object.getClass())) {
			final var annotation = field.getAnnotation(ResponseErrorProperty.class);
			if (annotation == null) {
				continue;
			}
			
			final var value = FieldUtils.readField(field, object, true);
			if (!annotation.includeIfNull() && value == null) {
				continue;
			}
			
			var property = annotation.value();
			if (StringUtils.isEmpty(property)) {
				property = field.getName();
			}
			
			extras.put(property, value);
		}
		
		for (final var method : MethodUtils.getMethodsWithAnnotation(object.getClass(), ResponseErrorProperty.class)) {
			final var annotation = method.getAnnotation(ResponseErrorProperty.class);
			
			if (method.getParameterCount() != 0) {
				continue;
			}
			
			final var value = method.invoke(object);
			if (!annotation.includeIfNull() && value == null) {
				continue;
			}
			
			var property = annotation.value();
			if (StringUtils.isEmpty(property)) {
				property = method.getName();
			}
			
			extras.put(property, value);
		}
		
		return extras;
	}
	
}