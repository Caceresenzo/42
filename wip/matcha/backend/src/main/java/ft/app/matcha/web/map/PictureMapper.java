package ft.app.matcha.web.map;

import ft.app.matcha.domain.picture.DefaultPicture;
import ft.app.matcha.domain.picture.Picture;
import ft.app.matcha.domain.picture.PictureService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.web.dto.PictureDto;
import ft.framework.mvc.domain.Page;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class PictureMapper {
	
	public static final long NO_DEFAULT = -1;
	
	private final PictureService pictureService;
	
	public Page<PictureDto> toDto(Page<Picture> page) {
		final var user = page.getContent().stream().findFirst().map(Picture::getUser).orElse(null);
		final var defaultId = getDefaultId(user);
		
		return page.map((picture) -> toDto(picture, defaultId));
	}
	
	public PictureDto toDto(Picture picture) {
		final var defaultId = getDefaultId(picture.getUser());
		
		return toDto(picture, defaultId);
	}
	
	public PictureDto toDto(Picture picture, long defaultId) {
		final var isDefault = defaultId == picture.getId();
		
		return toDefaultDto(picture)
			.setDefault(isDefault);
	}
	
	public PictureDto toDefaultDto(Picture picture) {
		return new PictureDto()
			.setId(picture.getId())
			.setUserId(picture.getUserId())
			.setDescription(picture.getDescription())
			.setDefault(true)
			.setCreatedAt(picture.getCreatedAt());
	}
	
	public long getDefaultId(User user) {
		if (user == null) {
			return NO_DEFAULT;
		}
		
		return pictureService.getDefault(user)
			.map(DefaultPicture::getPicture)
			.map(Picture::getId)
			.orElse(NO_DEFAULT);
	}
	
}