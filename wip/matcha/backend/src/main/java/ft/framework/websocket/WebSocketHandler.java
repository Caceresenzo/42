package ft.framework.websocket;

import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.concurrent.ConcurrentHashMap;

import org.eclipse.jetty.websocket.api.Session;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketClose;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketConnect;
import org.eclipse.jetty.websocket.api.annotations.OnWebSocketError;
import org.eclipse.jetty.websocket.api.annotations.WebSocket;

import com.fasterxml.jackson.databind.ObjectMapper;

import ft.framework.websocket.packet.ConnectListener;
import ft.framework.websocket.packet.Packet;
import lombok.Data;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;
import spark.Spark;

@Slf4j
@Data
@WebSocket
public class WebSocketHandler {
	
	private final ObjectMapper objectMapper;
	
	private ConnectListener connectListener;
	private final Map<Session, SocketConnection> connections = new ConcurrentHashMap<>();
	private final Map<String, Set<SocketConnection>> rooms = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
	
	@OnWebSocketConnect
	public void onConnect(Session session) throws Exception {
		log.trace("Session connected: {}", session.getRemoteAddress());
		
		final var connection = new SocketConnection(session, this);
		
		if (connectListener.test(connection)) {
			connections.put(session, connection);
		} else {
			connection.leaveAll();
			session.close();
		}
	}
	
	@OnWebSocketClose
	public void onClose(Session session, int statusCode, String reason) {
		log.trace("Session closed: {} (statusCode={}, reason={})", session.getRemoteAddress(), statusCode, reason);
		
		final var connection = connections.remove(session);
		if (connection == null) {
			return;
		}
		
		connection.leaveAll();
	}
	
	@OnWebSocketError
	public void onError(Session session, Throwable throwable) {
		log.trace("Session error: {} (throwable={})", session.getRemoteAddress(), throwable.getMessage());
		throwable.printStackTrace();
	}
	
	public void emit(String room, String event, Object payload) {
		final var connections = rooms.get(room);
		if (connections == null) {
			return;
		}
		
		final var json = convertToJson(event, payload);
		connections.forEach((connection) -> connection.emit(json));
	}
	
	@SneakyThrows
	public String convertToJson(String event, Object payload) {
		final var packet = new Packet(event, payload);
		return objectMapper.writeValueAsString(packet);
	}
	
	public static WebSocketHandler create(ObjectMapper objectMapper) {
		final var handler = new WebSocketHandler(objectMapper);
		
		final var path = "/websocket";
		Spark.webSocket(path, handler);
		log.info("Exposing {}", path);
		
		return handler;
	}
	
}