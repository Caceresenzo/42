package ft.framework.convert.converter.impl;

import java.time.Duration;

import ft.framework.convert.converter.Converter;

public class StringToDurationConverter implements Converter<String, Duration> {

	@Override
	public Duration convert(String source) {
		return Duration.parse(source);
	}
	
}