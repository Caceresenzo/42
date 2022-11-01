package ft.framework.convert.converter;

public interface Converter<S, T> {
	
	T convert(S source);
	
}