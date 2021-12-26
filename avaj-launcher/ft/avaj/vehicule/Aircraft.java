package ft.avaj.vehicule;

import ft.avaj.simulation.Weather;
import ft.avaj.simulation.WeatherTower;

public class Aircraft {
	
	/* UML: __-idCounter : long__ */
	private static long idCounter = 0;
	
	/* UML: #id : long */
	protected final long id;
	
	/* UML: #name : string */
	protected final String name;
	
	/* UML: #coordinates : Coordinates */
	protected final Coordinates coordinates;
	
	/* UML: #Aircraft(name : string, coordinates : Coordinates) */
	protected Aircraft(String name, Coordinates coordinates) {
		this.name = name;
		this.coordinates = coordinates;
		
		/* Each time an aircraft is created, it receives a unique ID. */
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
	
	/* If an aircraft reaches height 0 or needs to go below it, the aircraft lands, unregisters from the weather tower and logs its current coordinates. */
	protected void logLanding() {
		System.out.println(String.format("%s landing. (%s)", toString(), coordinates));
	}
	
	/* The message format is: TYPE#NAME(UNIQUE_ID): SPECIFIC_MESSAGE. */
	protected void log(String message) {
		System.out.println(String.format("%s: %s", toString(), message));
	}
	
	/* UML: -nextId() : long */
	private long nextId() {
		return idCounter++;
	}
	
}