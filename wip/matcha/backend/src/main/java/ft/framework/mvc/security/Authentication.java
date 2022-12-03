package ft.framework.mvc.security;

import java.security.Principal;

public interface Authentication extends Principal {
	
	Object getPrincipal();
	
	boolean isAuthenticated();
	
	void setAuthenticated(boolean state);
	
}