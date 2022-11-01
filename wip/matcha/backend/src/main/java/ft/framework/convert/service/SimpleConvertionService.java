package ft.framework.convert.service;

import java.lang.reflect.ParameterizedType;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.lang3.tuple.Pair;

import ft.framework.convert.converter.Converter;
import ft.framework.convert.converter.impl.StringToNumberConverter;
import ft.framework.convert.converter.impl.StringToUUIDConverter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SimpleConvertionService implements ConvertionService {
	
	private final Map<Class<?>, Map<Class<?>, Converter<?, ?>>> converters;
	
	public SimpleConvertionService() {
		this.converters = new HashMap<>();
		
		loadDefaults();
	}
	
	private void loadDefaults() {
		register(new StringToUUIDConverter());
		
		final var stringToLongConverter = new StringToNumberConverter(Long::parseLong);
		register(long.class, stringToLongConverter);
		register(Long.class, stringToLongConverter);
		
		final var stringToIntConverter = new StringToNumberConverter(Integer::parseInt);
		register(int.class, stringToIntConverter);
		register(Integer.class, stringToIntConverter);
	}
	
	public void register(Converter<?, ?> converter) {
		final var types = extractTypes(converter);
		
		if (types != null) {
			register(types.getLeft(), types.getRight(), converter);
		}
	}
	
	public void register(Class<?> targetType, Converter<?, ?> converter) {
		final var types = extractTypes(converter);
		
		if (types != null) {
			register(types.getLeft(), targetType, converter);
		}
	}
	
	public void register(Class<?> sourceType, Class<?> targetType, Converter<?, ?> converter) {
		log.info("Registered converter: {} to {}", sourceType.getSimpleName(), targetType.getSimpleName());
		
		converters
			.computeIfAbsent(sourceType, (key) -> new HashMap<>())
			.put(targetType, converter);
	}
	
	public Pair<Class<?>, Class<?>> extractTypes(Converter<?, ?> converter) {
		final var clazz = converter.getClass();
		
		for (final var type : clazz.getGenericInterfaces()) {
			if (type instanceof ParameterizedType parameterizedType && Converter.class.equals(parameterizedType.getRawType())) {
				final var typeArguments = parameterizedType.getActualTypeArguments();
				
				final var sourceType = (Class<?>) typeArguments[0];
				final var targetType = (Class<?>) typeArguments[1];
				
				return Pair.of(sourceType, targetType);
			}
		}
		
		return null;
	}
	
	@SuppressWarnings({ "unchecked" })
	@Override
	public Object convert(Object value, Class<?> sourceType, Class<?> targetType) {
		if (sourceType.equals(targetType)) {
			return value;
		}
		
		final var converter = findConverter(sourceType, targetType);
		return converter.convert(value);
	}
	
	@SuppressWarnings({ "rawtypes" })
	public Converter findConverter(Class<?> sourceType, Class<?> targetType) {
		Converter converter = converters
			.getOrDefault(sourceType, Collections.emptyMap())
			.get(targetType);
		
		if (converter == null) {
			throw new IllegalArgumentException(String.format("no conversion for %s and %s", sourceType, targetType));
		}
		
		return converter;
	}
	
}