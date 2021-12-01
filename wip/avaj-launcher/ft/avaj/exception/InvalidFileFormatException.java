package ft.avaj.exception;

/* You create your own custom exceptions for treating abnormal behaviour. */
public class InvalidFileFormatException extends RuntimeException {
	
	private static final long serialVersionUID = 3356460292807735512L;
	
	public InvalidFileFormatException(String message) {
		super(message);
	}
	
}