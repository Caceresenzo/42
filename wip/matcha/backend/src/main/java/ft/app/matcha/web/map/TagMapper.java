package ft.app.matcha.web.map;

import ft.app.matcha.domain.tag.Tag;
import ft.app.matcha.domain.tag.UserTagService;
import ft.app.matcha.web.dto.TagDto;
import lombok.AllArgsConstructor;

@AllArgsConstructor
public class TagMapper {
	
	private final UserTagService userTagService;
	
	public TagDto toDto(Tag tag) {
		final var usage = userTagService.countByTag(tag);
		
		return new TagDto()
			.setId(tag.getId())
			.setName(tag.getName())
			.setColor(tag.getColor())
			.setUsage(usage)
			.setCreatedAt(tag.getCreatedAt());
	}
	
}