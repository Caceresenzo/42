package ft.avaj.vehicule;

import ft.avaj.simulation.WeatherTower;

public class Helicopter extends Aircraft implements Flyable {
	
	/* UML: -weatherTower : WeatherTower */
	private WeatherTower weatherTower;
	
	/* UML: ~Helicopter(name : string, coordinates : Coordinates) */
	Helicopter(String name, Coordinates coordinates) {
		super(name, coordinates);
	}
	
	/* UML: +updateConditions() : void */
	@Override
	public void updateConditions() {
		switch (getCurrentWeather(weatherTower)) {
			case SUN: {
				/* Longitude increases with 10, Height increases with 2. */
				coordinates.addLongitude(10);
				coordinates.addHeight(2);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("The view is clear!");
				
				break;
			}
			
			case RAIN: {
				/* Longitude increases with 5. */
				coordinates.addLongitude(5);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Avoiding rain.");
				
				break;
			}
			
			case FOG: {
				/* Longitude increases with 1. */
				coordinates.addLongitude(1);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Its getting difficult to see.");
				
				break;
			}
			
			case SNOW: {
				/* Height decreases with 12. */
				coordinates.addHeight(-12);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("The snow might be too dangerous!");
				
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