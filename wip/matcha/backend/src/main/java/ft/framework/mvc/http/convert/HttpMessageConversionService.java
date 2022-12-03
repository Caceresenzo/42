package ft.framework.mvc.http.convert;

import java.io.InputStream;
import java.io.OutputStream;

public interface HttpMessageConversionService {
	
	Object read(Class<?> clazz, String mediaType, InputStream inputStream);
	
	void write(Object value, Class<?> clazz, String contentType, OutputStream outputStream);
	
}