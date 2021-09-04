package ft.avaj.exception;

public class TooMuchArgumentException extends RuntimeException {
	
	private static final long serialVersionUID = -6270911488212254019L;
	
	public TooMuchArgumentException(int got) {
		super(String.format("expected 1 argument, got %s", got));
	}
	
}