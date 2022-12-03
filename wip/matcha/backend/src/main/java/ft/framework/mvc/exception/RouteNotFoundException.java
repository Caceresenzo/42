package ft.framework.mvc.exception;

import org.eclipse.jetty.http.HttpStatus;

import ft.framework.mvc.annotation.ResponseErrorProperty;
import ft.framework.mvc.annotation.ResponseStatus;
import lombok.Getter;

@SuppressWarnings("serial")
@Getter
@ResponseStatus(HttpStatus.NOT_FOUND_404)
public class RouteNotFoundException extends RuntimeException {
	
	@ResponseErrorProperty
	private final String path;
	
	public RouteNotFoundException(String path) {
		super("route not found");
		
		this.path = path;
	}
	
}