package ft.app.matcha.domain.auth;

import org.apache.commons.codec.digest.DigestUtils;

public class PasswordEncoder {
	
	public static String encode(String input) {
		return DigestUtils.md5Hex(input);
	}
	
}