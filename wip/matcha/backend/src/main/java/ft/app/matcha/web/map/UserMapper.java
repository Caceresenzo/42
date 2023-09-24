package ft.app.matcha.web.map;

import ft.app.matcha.domain.heartbeat.HeartbeatService;
import ft.app.matcha.domain.location.LocationService;
import ft.app.matcha.domain.picture.DefaultPicture;
import ft.app.matcha.domain.picture.PictureService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.web.dto.UserDto;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class UserMapper {
	
	private final RelationshipMapper relationshipMapper;
	private final PictureService pictureService;
	private final PictureMapper pictureMapper;
	private final HeartbeatService heartbeatService;
	private final LocationService locationService;
	private final LocationMapper locationMapper;
	
	public UserDto toDto(User user) {
		final var picture = pictureService.getDefault(user)
			.map(DefaultPicture::getPicture)
			.map(pictureMapper::toDefaultDto)
			.orElse(null);
		
		final var presence = heartbeatService.getPresence(user);
		final var location = locationMapper.toDto(locationService.find(user));
		
		return new UserDto()
			.setId(user.getId())
			.setLogin(user.getLogin())
			.setFirstName(user.getFirstName())
			.setLastName(user.getLastName())
			.setBiography(user.getBiography())
			.setGender(user.getGender())
			.setSexualOrientation(user.getSexualOrientation())
			.setFame(user.getFame())
			.setEmailConfirmed(user.isEmailConfirmed())
			.setPicture(picture)
			.setLocation(location)
			.setPresence(presence);
	}
	
	public UserDto toDto(User user, User principal) {
		if (principal == null) {
			return toDto(user);
		} else {
			return toDtoAuthenticated(user, principal);
		}
	}
	
	private UserDto toDtoAuthenticated(User user, User principal) {
		final var relationship = relationshipMapper.toDto(principal, user);
		final var email = user.getId() == principal.getId() ? user.getEmail() : null;
		
		return toDto(user)
			.setEmail(email)
			.setRelationship(relationship);
	}
	
}