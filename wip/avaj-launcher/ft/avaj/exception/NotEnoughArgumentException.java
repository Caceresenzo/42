package ft.avaj.exception;

public class NotEnoughArgumentException extends RuntimeException {
	
	private static final long serialVersionUID = 3759453784687176874L;
	
	public NotEnoughArgumentException() {
		super("expected 1 argument, got zero");
	}
	
}