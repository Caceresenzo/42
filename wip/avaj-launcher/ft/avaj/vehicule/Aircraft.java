package ft.avaj.vehicule;

import ft.avaj.simulation.Weather;
import ft.avaj.simulation.WeatherTower;

public class Aircraft {
	
	private static long idCounter = 0;
	
	protected final long id;
	protected final String name;
	protected final Coordinates coordinates;
	
	public Aircraft(String name, Coordinates coordinates) {
		this.name = name;
		this.coordinates = coordinates;
		
		this.id = nextId();
	}
	
	protected Weather getCurrentWeather(WeatherTower weatherTower) {
		String weather = weatherTower.getWeather(coordinates);
		
		return Weather.valueOf(weather);
	}
	
	@Override
	public String toString() {
		return String.format("%s#%s(%s)", getClass().getSimpleName(), name, id);
	}
	
	protected void logLanding() {
		System.out.println(String.format("%s landing.", toString()));
	}

	protected void log(String message) {
		System.out.println(String.format("%s: %s", toString(), message));
	}
	
	private static long nextId() {
		return idCounter++;
	}
	
}