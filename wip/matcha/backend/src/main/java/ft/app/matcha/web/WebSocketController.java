package ft.app.matcha.web;

import java.net.HttpCookie;

import org.apache.commons.lang3.StringUtils;

import ft.app.matcha.domain.message.event.MessageCreatedEvent;
import ft.app.matcha.domain.notification.event.NotificationCreatedEvent;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.security.jwt.JwtAuthenticator;
import ft.app.matcha.security.jwt.JwtCookieAuthenticationFilter;
import ft.framework.event.annotation.EventListener;
import ft.framework.websocket.WebSocketHandler;

public class WebSocketController {
	
	public static final String MESSAGE_CREATED_EVENT = "message.created";
	public static final String NOTIFICATION_CREATED_EVENT = "notification.created";
	
	private final WebSocketHandler webSocket;
	
	public WebSocketController(WebSocketHandler webSocket, JwtAuthenticator jwtAuthenticator) {
		this.webSocket = webSocket;
		
		webSocket.setConnectListener((connection) -> {
			try {
				final var accessToken = connection.getCookie(JwtCookieAuthenticationFilter.ACCESS_TOKEN_COOKIE)
					.map(HttpCookie::getValue)
					.orElse(null);
				
				if (StringUtils.isNotBlank(accessToken)) {
					final var authentication = jwtAuthenticator.authenticate(accessToken);
					
					if (authentication != null) {
						connection.setAuthentication(authentication);
						
						if (authentication.getPrincipal() instanceof User user) {
							connection.join(toUserRoom(user));
						}
						
						return true;
					}
				}
			} catch (Exception exception) {
			}
			
			return false;
		});
	}
	
	@EventListener
	public void onMessageCreated(MessageCreatedEvent event) {
		final var message = event.getMessage();
		
		sendToUser(message.getUser(), MESSAGE_CREATED_EVENT, message);
		sendToUser(message.getPeer(), MESSAGE_CREATED_EVENT, message);
	}
	
	@EventListener
	public void onNotificationCreated(NotificationCreatedEvent event) {
		final var notification = event.getNotification();
		
		sendToUser(notification.getUser(), NOTIFICATION_CREATED_EVENT, notification);
	}
	
	public <T> void sendToUser(User user, String event, T payload) {
		final var room = toUserRoom(user);
		
		webSocket.emit(room, event, payload);
	}
	
	public static String toUserRoom(User user) {
		return "user-%s".formatted(user.getId());
	}
	
}