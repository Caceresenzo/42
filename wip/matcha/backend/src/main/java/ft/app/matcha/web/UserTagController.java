package ft.app.matcha.web;

import ft.app.matcha.domain.tag.Tag;
import ft.app.matcha.domain.tag.TagService;
import ft.app.matcha.domain.tag.UserTagService;
import ft.app.matcha.domain.tag.exception.TagNotFoundException;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.user.UserService;
import ft.app.matcha.domain.user.exception.OnlyYourselfException;
import ft.app.matcha.domain.user.exception.UserNotFoundException;
import ft.app.matcha.web.dto.TagDto;
import ft.app.matcha.web.map.TagMapper;
import ft.framework.mvc.annotation.Authenticated;
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
@RequestMapping(path = "/users/{userId}/tags")
@RequiredArgsConstructor
public class UserTagController {
	
	private final UserTagService userTagService;
	private final UserService userService;
	private final TagService tagService;
	private final TagMapper tagMapper;
	
	@GetMapping
	@ApiOperation(summary = "List user's tags.")
	public Page<TagDto> list(
		Pageable pageable,
		@Variable long userId
	) {
		final var user = getUser(userId);
		
		return userTagService.findAll(user, pageable)
			.map(tagMapper::toDto);
	}
	
	@Authenticated
	@PostMapping(path = "{tagId}")
	@ApiOperation(summary = "Add a tag to the user's tags.")
	public boolean add(
		@Variable long userId,
		@Variable long tagId,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var tag = getTag(tagId);
		
		return userTagService.add(user, tag);
	}
	
	@Authenticated
	@DeleteMapping(path = "{tagId}")
	@ApiOperation(summary = "Remove a tag from the user's tags.")
	public boolean remove(
		@Variable long userId,
		@Variable long tagId,
		@Principal User user
	) {
		ensureSelf(userId, user);
		
		final var tag = getTag(tagId);
		
		return userTagService.remove(user, tag);
	}
	
	public User getUser(long userId) {
		return userService.find(userId)
			.orElseThrow(() -> new UserNotFoundException(userId));
	}
	
	public Tag getTag(long tagId) {
		return tagService.find(tagId)
			.orElseThrow(() -> new TagNotFoundException(tagId));
	}
	
	public void ensureSelf(long userId, User currentUser) {
		if (userId != currentUser.getId()) {
			throw new OnlyYourselfException();
		}
	}
	
}