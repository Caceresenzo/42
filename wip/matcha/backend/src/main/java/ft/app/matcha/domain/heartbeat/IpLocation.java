package ft.app.matcha.domain.heartbeat;

public record IpLocation(
	String country,
	String city,
	Double latitude,
	Double longitude
) {}