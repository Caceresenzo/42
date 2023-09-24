package ft.app.matcha.domain.auth.exception;

import lombok.experimental.StandardException;

@SuppressWarnings("serial")
@StandardException
public class JwtSignatureException extends JwtException {
	
	public static final String MESSAGE = "signature is invalid";
	
	public JwtSignatureException() {
		super(MESSAGE);
	}
	
	public JwtSignatureException(Throwable cause) {
		super(MESSAGE, cause);
	}
	
}