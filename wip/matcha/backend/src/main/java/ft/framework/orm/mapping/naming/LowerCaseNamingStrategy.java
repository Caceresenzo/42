package ft.framework.orm.mapping.naming;

import java.util.Arrays;
import java.util.stream.Collectors;

import org.apache.commons.lang3.StringUtils;

public enum LowerCaseNamingStrategy implements NamingStrategy {
	
	INSTANCE;
	
	@Override
	public String convertName(String camelCase) {
		return Arrays.stream(StringUtils.splitByCharacterTypeCamelCase(camelCase))
			.map(String::toLowerCase)
			.collect(Collectors.joining("_"));
	}
	
}