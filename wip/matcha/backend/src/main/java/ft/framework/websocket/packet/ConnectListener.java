package ft.framework.websocket.packet;

import java.util.function.Predicate;

import ft.framework.websocket.SocketConnection;

@FunctionalInterface
public interface ConnectListener extends Predicate<SocketConnection> {
	
}