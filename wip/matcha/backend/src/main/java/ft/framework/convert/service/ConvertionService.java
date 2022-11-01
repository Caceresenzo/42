package ft.framework.convert.service;

public interface ConvertionService {
	
	Object convert(Object value, Class<?> sourceType, Class<?> targetType);
	
}