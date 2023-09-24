package ft.app.matcha.domain.tag;

import java.util.regex.Pattern;

public class TagFormatter {
	
	public static final Pattern ILLEGAL_CHARACTERS = Pattern.compile("[^a-z0-9]|\\s+");
	public static final Pattern DASH = Pattern.compile("-+");
	
	public static String format(String input) {
		input = input.toLowerCase();
		input = ILLEGAL_CHARACTERS.matcher(input).replaceAll("-");
		input = DASH.matcher(input).replaceAll("-");
		
		return input;
	}
	
}