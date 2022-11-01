package ft.framework.convert.converter.impl;

import java.util.function.Function;

import ft.framework.convert.converter.Converter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class StringToNumberConverter implements Converter<String, Number> {
	
	private final Function<String, Number> parser;
	
	@Override
	public Number convert(String source) {
		return parser.apply(source);
	}
	
}