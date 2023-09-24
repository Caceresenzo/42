package ft.framework.websocket;

import java.net.HttpCookie;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import org.eclipse.jetty.websocket.api.Session;
import org.eclipse.jetty.websocket.api.WriteCallback;

import ft.framework.mvc.security.AnonymousAuthentication;
import ft.framework.mvc.security.Authentication;
import lombok.AccessLevel;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.Getter;
import lombok.SneakyThrows;

@Data
@EqualsAndHashCode(onlyExplicitlyIncluded = true)
public class SocketConnection {
	
	@EqualsAndHashCode.Include
	private final Session session;
	private final WebSocketHandler handler;
	
	@Getter(AccessLevel.PACKAGE)
	private final Set<String> rooms = ConcurrentHashMap.newKeySet();
	
	private Authentication authentication = AnonymousAuthentication.INSTANCE;
	
	public void join(String room) {
		synchronized (handler) {
			handler.getRooms()
				.computeIfAbsent(room, (key) -> ConcurrentHashMap.newKeySet())
				.add(this);
		}
	}
	
	public void leave(String room) {
		synchronized (handler) {
			final var connections = handler.getRooms().get(room);
			
			if (connections == null) {
				return;
			}
			
			connections.remove(this);
			
			if (connections.isEmpty()) {
				handler.getRooms().remove(room, connections);
			}
		}
	}
	
	public void leaveAll() {
		for (final var room : rooms) {
			leave(room);
		}
	}
	
	public void emit(String event, Object payload) {
		final var json = handler.convertToJson(event, payload);
		emit(json);
	}
	
	public void emit(String message) {
		session.getRemote().sendString(message, NothingWriteCallback.INSTANCE);
	}
	
	@SneakyThrows
	public void close() {
		session.disconnect();
	}
	
	private static enum NothingWriteCallback implements WriteCallback {
		
		INSTANCE;
		
		@Override
		public void writeFailed(Throwable x) {
		}
		
		@Override
		public void writeSuccess() {
		}
		
	}
	
	public Optional<HttpCookie> getCookie(String name) {
		for (final var cookie : session.getUpgradeRequest().getCookies()) {
			if (name.equals(cookie.getName())) {
				return Optional.of(cookie);
			}
		}
		
		return Optional.empty();
	}
	
}