package ft.app.matcha.domain.auth.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.app.matcha.domain.auth.Token;
import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@ResponseStatus(HttpStatus.FORBIDDEN_403)
@SuppressWarnings("serial")
@Getter
public class InvalidTokenException extends RuntimeException {
	
	@ResponseErrorProperty
	private final Token.Type type;
	
	public InvalidTokenException(Token.Type type) {
		super("unknown token");
		
		this.type = type;
	}
	
}