package ft.framework.convert.converter.impl;

import java.util.UUID;

import ft.framework.convert.converter.Converter;

public class StringToUUIDConverter implements Converter<String, UUID> {

	@Override
	public UUID convert(String source) {
		return UUID.fromString(source);
	}
	
}