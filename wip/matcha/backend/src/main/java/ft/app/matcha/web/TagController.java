package ft.app.matcha.web;

import ft.app.matcha.domain.tag.Tag;
import ft.app.matcha.domain.tag.TagService;
import ft.app.matcha.domain.tag.UserTagService;
import ft.app.matcha.domain.tag.exception.TagNotFoundException;
import ft.app.matcha.web.dto.TagDto;
import ft.app.matcha.web.dto.UserDto;
import ft.app.matcha.web.form.TagCreateForm;
import ft.app.matcha.web.map.TagMapper;
import ft.app.matcha.web.map.UserMapper;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PostMapping;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.swagger.annotation.ApiOperation;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;
import spark.utils.StringUtils;

@Controller
@RequestMapping(path = "/tags")
@RequiredArgsConstructor
public class TagController {
	
	private final TagService tagService;
	private final UserTagService userTagService;
	private final TagMapper tagMapper;
	private final UserMapper userMapper;
	
	@GetMapping
	@ApiOperation(summary = "List tags with a query.")
	public Page<TagDto> list(
		Pageable pageable,
		@Query(required = false) String query
	) {
		return doList(pageable, query)
			.map(tagMapper::toDto);
	}
	
	public Page<Tag> doList(Pageable pageable, String query) {
		if (StringUtils.isNotBlank(query)) {
			return tagService.search(query, pageable);
		}
		
		return tagService.findAll(pageable);
	}
	
	@PostMapping
	@ApiOperation(summary = "Create a tag.")
	public TagDto create(
		@Body @Valid TagCreateForm form
	) {
		final var tag = tagService.create(form.getName(), form.getColor());
		return tagMapper.toDto(tag);
	}
	
	@GetMapping(path = "{tagId}")
	@ApiOperation(summary = "Show a tag.")
	public TagDto show(
		@Variable long tagId
	) {
		final var tag = getTag(tagId);
		
		return tagMapper.toDto(tag);
	}
	
	@GetMapping(path = "{tagId}/users")
	@ApiOperation(summary = "Show a tag.")
	public Page<UserDto> listUsers(
		Pageable pageable,
		@Variable long tagId
	) {
		final var tag = getTag(tagId);
		
		return userTagService.findAll(tag, pageable)
			.map(userMapper::toDto);
	}
	
	public Tag getTag(long tagId) {
		return tagService.find(tagId)
			.orElseThrow(() -> new TagNotFoundException(tagId));
	}
	
}