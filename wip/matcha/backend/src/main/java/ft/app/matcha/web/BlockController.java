package ft.app.matcha.web;

import ft.app.matcha.domain.relationship.Relationship;
import ft.app.matcha.domain.relationship.RelationshipService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.OnlyYourselfException;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.web.dto.UserDto;
import ft.app.matcha.web.form.LikeForm;
import ft.app.matcha.web.map.UserMapper;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.DeleteMapping;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.swagger.annotation.ApiOperation;
import lombok.RequiredArgsConstructor;

@Controller
@RequestMapping(path = "/users/{userId}/blocks")
@RequiredArgsConstructor
@Authenticated
public class BlockController {
	
	private final RelationshipService relationshipService;
	private final UserService userService;
	private final UserMapper userMapper;
	
	@GetMapping
	@ApiOperation(summary = "List users that a user blocked.")
	public Page<UserDto> list(
		@Variable long userId,
		Pageable pageable,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		return relationshipService.findAllByUser(user, Relationship.Type.BLOCK, pageable)
			.map((relationship) -> userMapper.toDto(relationship.getPeer(), user));
	}
	
	@PostMapping
	@ApiOperation(summary = "Block a user.")
	public UserDto block(
		@Variable long userId,
		@Body LikeForm form,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var peer = getUser(form.getPeerId());
		final var block = relationshipService.block(user, peer);
		
		return userMapper.toDto(block.getPeer(), user);
	}
	
	@Authenticated
	@DeleteMapping(path = "{peerId}")
	@ApiOperation(summary = "Unblock a peer.")
	public void unblock(
		@Variable long userId,
		@Variable long peerId,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var peer = getUser(peerId);
		
		relationshipService.unblock(user, peer);
	}
	
	public void ensureSelf(long userId, User currentUser) {
		if (userId != currentUser.getId()) {
			throw new OnlyYourselfException();
		}
	}
	
	public User getUser(long id) {
		return userService.find(id)
			.orElseThrow(() -> new UserNotFoundException(id));
	}
	
}