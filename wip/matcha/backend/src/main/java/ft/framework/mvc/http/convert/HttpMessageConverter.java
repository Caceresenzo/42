package ft.framework.mvc.http.convert;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;

public interface HttpMessageConverter<T> {
	
	boolean canRead(Class<?> clazz, String mediaType);
	
	boolean canWrite(Class<?> clazz, String mediaType);
	
	List<String> getSupportedMediaTypes();
	
	default List<String> getSupportedMediaTypes(Class<?> clazz) {
		return getSupportedMediaTypes();
	}
	
	T read(Class<? extends T> clazz, InputStream inputStream);
	
	void write(T value, String contentType, OutputStream outputStream);
	
}