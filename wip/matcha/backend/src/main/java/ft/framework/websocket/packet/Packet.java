package ft.framework.websocket.packet;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Packet {
	
	private String event;
	private Object payload;
	
}