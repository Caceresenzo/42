package ft.app.matcha.domain.auth.event;

import ft.app.matcha.domain.auth.Token;
import ft.app.matcha.domain.user.User;
import ft.framework.event.ApplicationEvent;
import lombok.Getter;

@Getter
@SuppressWarnings("serial")
public class TokenValidatedEvent extends ApplicationEvent {
	
	private final User user;
	private final Token.Type type;
	
	public TokenValidatedEvent(Object source, Token token) {
		this(source, token.getUser(), token.getType());
	}
	
	public TokenValidatedEvent(Object source, User user, Token.Type type) {
		super(source);
		
		this.user = user;
		this.type = type;
	}
	
}