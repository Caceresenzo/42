package ft.framework.orm.mapping.naming;

import org.apache.commons.lang3.StringUtils;

public interface NamingStrategy {
	
	String convertName(String camelCase);
	
	default String convertNameIfEmpty(String value, String camelCase) {
		if (StringUtils.isNotEmpty(value)) {
			return value;
		}
		
		return convertName(camelCase);
	}
	
	default String convertIdNameIfEmpty(String value, String camelCase) {
		if (StringUtils.isNotEmpty(value)) {
			return value;
		}
		
		return convertName(camelCase) + "_id";
	}
	
}