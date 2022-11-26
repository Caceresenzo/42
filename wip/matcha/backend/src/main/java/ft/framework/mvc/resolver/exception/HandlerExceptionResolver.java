package ft.framework.mvc.resolver.exception;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import ft.framework.mvc.Problem;

public interface HandlerExceptionResolver {
	
	Problem resolveException(HttpServletRequest request, HttpServletResponse response, Exception exception);
	
}