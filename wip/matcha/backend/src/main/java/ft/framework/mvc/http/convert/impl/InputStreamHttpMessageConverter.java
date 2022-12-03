package ft.framework.mvc.http.convert.impl;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.Collections;
import java.util.List;

import ft.framework.mvc.http.convert.HttpMessageConverter;
import ft.framework.util.MediaTypes;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;

@RequiredArgsConstructor
public class InputStreamHttpMessageConverter implements HttpMessageConverter<InputStream> {
	
	public static final String BYTES = MediaTypes.BYTES;
	public static final List<String> SUPPORTED = Collections.singletonList(BYTES);
	
	@Override
	public boolean canRead(Class<?> clazz, String mediaType) {
		return false;
	}
	
	@Override
	public boolean canWrite(Class<?> clazz, String mediaType) {
		return clazz.isAssignableFrom(InputStream.class);
	}
	
	@Override
	public List<String> getSupportedMediaTypes() {
		return SUPPORTED;
	}
	
	@Override
	public InputStream read(Class<? extends InputStream> clazz, InputStream inputStream) {
		throw new UnsupportedOperationException();
	}
	
	@SneakyThrows
	@Override
	public void write(InputStream value, String contentType, OutputStream outputStream) {
		value.transferTo(outputStream);
	}
	
}