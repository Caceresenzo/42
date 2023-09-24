package ft.app.matcha.web;

import ft.app.matcha.domain.message.Message;
import ft.app.matcha.domain.message.MessageService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.web.form.MessageCreateForm;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.swagger.annotation.ApiOperation;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;

@Controller
@RequestMapping(path = "/messages")
@RequiredArgsConstructor
public class MessageController {
	
	private final MessageService messageService;
	private final UserService userService;
	
	@Authenticated
	@GetMapping
	@ApiOperation(summary = "List messages with a peer.")
	public Page<Message> list(
		Pageable pageable,
		@Query long peerId,
		@Principal User currentUser
	) {
		final var peer = userService.find(peerId)
			.orElseThrow(() -> new UserNotFoundException(peerId));
		
		return messageService.findAll(currentUser, peer, pageable);
	}
	
	@Authenticated
	@PostMapping
	@ApiOperation(summary = "Send a message to a peer.")
	public Message create(
		@Body @Valid MessageCreateForm form,
		@Principal User currentUser
	) {
		final var peerId = form.getPeerId();
		final var peer = userService.find(peerId)
			.orElseThrow(() -> new UserNotFoundException(peerId));
		
		return messageService.create(currentUser, peer, form.getContent());
	}
	
}