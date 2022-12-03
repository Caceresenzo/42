package ft.framework.mvc.http.convert.impl;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Collections;
import java.util.List;

import com.fasterxml.jackson.databind.ObjectMapper;

import ft.framework.mvc.http.convert.HttpMessageConverter;
import ft.framework.util.MediaTypes;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;

@RequiredArgsConstructor
public class JacksonHttpMessageConverter implements HttpMessageConverter<Object> {
	
	public static final String JSON = MediaTypes.JSON;
	public static final List<String> SUPPORTED = Collections.singletonList(JSON);
	
	private final ObjectMapper objectMapper;
	private final boolean buffered;

	@Override
	public boolean canRead(Class<?> clazz, String mediaType) {
		return mediaType.equals(JSON);
	}

	@Override
	public boolean canWrite(Class<?> clazz, String mediaType) {
		return mediaType.equals(JSON);
	}

	@Override
	public List<String> getSupportedMediaTypes() {
		return SUPPORTED;
	}

	@SneakyThrows
	@Override
	public Object read(Class<? extends Object> clazz, InputStream inputStream) {
		return objectMapper.readValue(inputStream, clazz);
	}

	@SneakyThrows
	@Override
	public void write(Object value, String contentType, OutputStream outputStream) {
		if (buffered) {
			final var bytes = objectMapper.writeValueAsBytes(value);
			outputStream.write(bytes);
		} else {
			objectMapper.writeValue(outputStream, value);
		}
	}
	
}