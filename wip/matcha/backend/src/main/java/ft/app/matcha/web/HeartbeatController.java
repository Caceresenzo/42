package ft.app.matcha.web;

import java.net.InetAddress;

import ft.app.matcha.domain.heartbeat.Heartbeat;
import ft.app.matcha.domain.heartbeat.HeartbeatService;
import ft.app.matcha.domain.user.User;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.swagger.annotation.ApiOperation;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Controller
@RequestMapping(path = "/heartbeat")
public class HeartbeatController {
	
	private final HeartbeatService heartbeatService;
	
	@GetMapping(path = "/log")
	@Authenticated
	@ApiOperation(summary = "Log your presence")
	public Heartbeat log(
		@Principal User principal,
		InetAddress inetAddress
	) {
		return heartbeatService.log(principal, inetAddress);
	}
	
}