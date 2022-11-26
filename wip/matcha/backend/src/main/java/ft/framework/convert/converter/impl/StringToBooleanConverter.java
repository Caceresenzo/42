package ft.framework.convert.converter.impl;

import ft.framework.convert.converter.Converter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class StringToBooleanConverter implements Converter<String, Boolean> {
	
	@Override
	public Boolean convert(String source) {
		return Boolean.parseBoolean(source);
	}
	
}