package ft.framework.util;

import java.io.IOException;

import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.deser.std.StringDeserializer;

@SuppressWarnings("serial")
public class StringTrimDeserializer extends StringDeserializer {
	
	@Override
	public String deserialize(JsonParser p, DeserializationContext ctxt) throws IOException {
		String value = super.deserialize(p, ctxt);
		return value != null ? value.trim() : null;
	}
	
}