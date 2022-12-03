package ft.framework.mvc.http.convert;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;

import ft.framework.mvc.exception.UnsupportedMediaTypeException;
import lombok.Builder;
import lombok.Singular;

@SuppressWarnings({ "rawtypes", "unchecked" })
@Builder
public class SimpleHttpMessageConversionService implements HttpMessageConversionService {
	
	@Singular
	private final List<HttpMessageConverter> converters;
	
	@Override
	public Object read(Class clazz, String mediaType, InputStream inputStream) {
		final var converter = getReadConverter(clazz, mediaType);
		
		return converter.read(clazz, inputStream);
	}
	
	@Override
	public void write(Object value, Class<?> clazz, String contentType, OutputStream outputStream) {
		final var converter = getWriteConverter(clazz, contentType);
		
		converter.write(value, contentType, outputStream);
	}
	
	public HttpMessageConverter getReadConverter(Class<?> clazz, String mediaType) {
		return converters.stream()
			.filter((converter) -> converter.canRead(clazz, mediaType))
			.findFirst()
			.orElseThrow(() -> new UnsupportedMediaTypeException(mediaType));
	}
	
	public HttpMessageConverter getWriteConverter(Class<?> clazz, String mediaType) {
		return converters.stream()
			.filter((converter) -> converter.canWrite(clazz, mediaType))
			.findFirst()
			.orElseThrow(() -> new UnsupportedMediaTypeException(mediaType));
	}
	
}