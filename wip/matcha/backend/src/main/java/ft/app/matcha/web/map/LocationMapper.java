package ft.app.matcha.web.map;

import java.util.Optional;

import ft.app.matcha.domain.location.Location;
import ft.app.matcha.web.dto.LocationDto;

public class LocationMapper {
	
	public LocationDto toDto(Location location) {
		if (!location.isShared()) {
			return new LocationDto()
				.setShared(false)
				.setUpdatedAt(location.getUpdatedAt());
		}
		
		return new LocationDto()
			.setShared(true)
			.setLatitude(location.getLatitude())
			.setLongitude(location.getLongitude())
			.setUpdatedAt(location.getUpdatedAt());
	}
	
	public LocationDto toDto(Optional<Location> location) {
		return location
			.map(this::toDto)
			.orElseGet(LocationDto::new);
	}
	
}