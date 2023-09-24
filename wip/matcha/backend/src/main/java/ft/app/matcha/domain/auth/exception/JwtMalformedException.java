package ft.app.matcha.domain.auth.exception;

import lombok.experimental.StandardException;

@SuppressWarnings("serial")
@StandardException
public class JwtMalformedException extends JwtException {
	
	public static final String MESSAGE = "signature is malformed";
	
	public JwtMalformedException() {
		super(MESSAGE);
	}
	
	public JwtMalformedException(Throwable cause) {
		super(MESSAGE, cause);
	}
	
}