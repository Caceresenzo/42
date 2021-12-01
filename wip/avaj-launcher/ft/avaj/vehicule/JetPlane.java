package ft.avaj.vehicule;

import ft.avaj.simulation.WeatherTower;

public class JetPlane extends Aircraft implements Flyable {
	
	/* UML: -weatherTower : WeatherTower */
	private WeatherTower weatherTower;
	
	/* UML: ~JetPlane(name : string, cooridnates : Coordinates) */
	JetPlane(String name, Coordinates coordinates) {
		super(name, coordinates);
	}
	
	/* UML: +updateConditions() : void */
	@Override
	public void updateConditions() {
		switch (getCurrentWeather(weatherTower)) {
			case SUN: {
				/* Latitude increases with 10, Height increases with 2. */
				coordinates.addLatitude(10);
				coordinates.addHeight(2);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Tango, going faster!");
				
				break;
			}
			
			case RAIN: {
				/* Latitude increases with 5. */
				coordinates.addLatitude(5);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Turning to avoid rain.");
				
				break;
			}
			
			case FOG: {
				/* Latitude increases with 1. */
				coordinates.addLatitude(1);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Turning to avoid fog.");
				
				break;
			}
			
			case SNOW: {
				/* Height decreases with 7. */
				coordinates.addHeight(-7);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Snow obscure view, going lower.");
				
				/* If an aircraft reaches height 0 or needs to go below it, the aircraft lands, unregisters from the weather tower and logs its current coordinates. */
				if (coordinates.isOnGround()) {
					logLanding();
					
					weatherTower.unregister(this);
				}
				
				break;
			}
		}
	}
	
	/* UML: +registerTower(weatherTower : WeatherTower) : void */
	@Override
	public void registerTower(WeatherTower weatherTower) {
		this.weatherTower = weatherTower;
	}
	
}