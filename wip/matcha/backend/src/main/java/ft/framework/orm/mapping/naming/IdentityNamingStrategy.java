package ft.framework.orm.mapping.naming;

public enum IdentityNamingStrategy implements NamingStrategy {
	
	INSTANCE;
	
	@Override
	public String convertName(String camelCase) {
		return camelCase;
	}
	
}