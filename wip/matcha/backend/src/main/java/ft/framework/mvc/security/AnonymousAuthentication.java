package ft.framework.mvc.security;

public enum AnonymousAuthentication implements Authentication {
	
	INSTANCE;
	
	@Override
	public String getName() {
		return "anonymous";
	}
	
	@Override
	public Object getPrincipal() {
		return null;
	}
	
	@Override
	public boolean isAuthenticated() {
		return false;
	}
	
	@Override
	public void setAuthenticated(boolean state) {
		throw new UnsupportedOperationException();
	}
	
}