package ft.app.matcha.web;

import ft.app.matcha.domain.relationship.Relationship;
import ft.app.matcha.domain.relationship.RelationshipService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.OnlyYourselfException;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.security.UserAuthentication;
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
import ft.framework.mvc.security.Authentication;
import ft.framework.swagger.annotation.ApiOperation;
import lombok.RequiredArgsConstructor;

@Controller
@RequestMapping(path = "/users/{userId}")
@RequiredArgsConstructor
public class LikeController {
	
	private final RelationshipService relationshipService;
	private final UserService userService;
	private final UserMapper userMapper;
	
	@GetMapping(path = "likers")
	@ApiOperation(summary = "List users that liked this user.")
	public Page<UserDto> listLikers(
		Pageable pageable,
		@Variable long userId,
		Authentication authentication
	) {
		final var principal = UserAuthentication.getUser(authentication);
		final var user = getUser(userId);
		
		return relationshipService.findAllByPeer(user, Relationship.Type.LIKE, pageable)
			.map((relationship) -> userMapper.toDto(relationship.getUser(), principal));
	}
	
	@GetMapping(path = "likes")
	@ApiOperation(summary = "List users that this user has liked.")
	public Page<UserDto> list(
		Pageable pageable,
		@Variable long userId,
		Authentication authentication
	) {
		final var principal = UserAuthentication.getUser(authentication);
		final var user = getUser(userId);
		
		return relationshipService.findAllByUser(user, Relationship.Type.LIKE, pageable)
			.map((relationship) -> userMapper.toDto(relationship.getPeer(), principal));
	}
	
	@Authenticated
	@PostMapping(path = "likes")
	@ApiOperation(summary = "Like a peer.")
	public UserDto like(
		@Variable long userId,
		@Body LikeForm form,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var peer = getUser(form.getPeerId());
		final var like = relationshipService.like(user, peer);
		
		return userMapper.toDto(like.getPeer(), user);
	}
	
	@Authenticated
	@DeleteMapping(path = "likes/{peerId}")
	@ApiOperation(summary = "Unlike a peer.")
	public void unlike(
		@Variable long userId,
		@Variable long peerId,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var peer = getUser(peerId);
		
		relationshipService.unlike(user, peer);
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