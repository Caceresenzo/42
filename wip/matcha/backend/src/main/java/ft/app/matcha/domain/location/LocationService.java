package ft.app.matcha.domain.location;

import java.time.LocalDateTime;
import java.util.Optional;

import ft.app.matcha.domain.heartbeat.event.HeartbeatEvent;
import ft.app.matcha.domain.user.User;
import ft.framework.event.annotation.EventListener;
import lombok.AllArgsConstructor;

@AllArgsConstructor
public class LocationService {
	
	private final LocationRepository repository;
	
	public Optional<Location> find(User user) {
		return repository.findByUser(user);
	}
	
	public synchronized Location get(User user) {
		return repository.findByUser(user)
			.orElseGet(() -> repository.save(
				new Location()
					.setUser(user)
			));
	}
	
	public Location update(User user, Double latitude, Double longitude) {
		final var location = get(user)
			.setShared(true)
			.setLatitude(latitude)
			.setLongitude(longitude)
			.setUpdatedAt(LocalDateTime.now());
		
		return repository.save(location);
	}
	
	public Location delete(User user) {
		final var location = get(user)
			.setShared(false)
			.setUpdatedAt(LocalDateTime.now());
		
		return repository.save(location);
	}
	
	@EventListener
	public void onHeartbeat(HeartbeatEvent event) {
		final var heartbeat = event.getHeartbeat();
		final var user = heartbeat.getUser();
		
		final var location = get(user);
		if (location.isShared()) {
			return;
		}
		
		if (heartbeat.getLatitude() == null || heartbeat.getLongitude() == null) {
			return;
		}
		
		repository.save(
			location
				.setLatitude(heartbeat.getLatitude())
				.setLongitude(heartbeat.getLongitude())
		);
	}
	
}