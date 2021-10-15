package ft.avaj.exception;

public class InvalidFileFormatException extends RuntimeException {
	
	private static final long serialVersionUID = 3356460292807735512L;
	
	public InvalidFileFormatException(String message) {
		super(message);
	}
	
}