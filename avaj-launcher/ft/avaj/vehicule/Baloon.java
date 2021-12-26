package ft.avaj.vehicule;

import ft.avaj.simulation.Weather;
import ft.avaj.simulation.WeatherTower;

public class Baloon extends Aircraft implements Flyable {
	
	/* UML: -weatherTower : WeatherTower */
	private WeatherTower weatherTower;
	
	/* UML: ~Baloon(name : string, coordinates : Coordinates) */
	Baloon(String name, Coordinates coordinates) {
		super(name, coordinates);
	}
	
	/* UML: +updateConditions() : void */
	@Override
	public void updateConditions() {
		Weather weather = getCurrentWeather(weatherTower);
		
		switch (weather) {
			case SUN: {
				/* Longitude increases with 2, Height increases with 4. */
				coordinates.addLongitude(2);
				coordinates.addHeight(4);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("I hope the air isn't too hot?");
				
				break;
			}
			
			case RAIN: {
				/* Height decreases with 5. */
				coordinates.addHeight(-5);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Its wetting my baloon!");
				
				break;
			}
			
			case FOG: {
				/* Height decreases with 3. */
				coordinates.addHeight(-3);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("I can't see anything...");
				
				break;
			}
			
			case SNOW: {
				/* Height decreases with 15. */
				coordinates.addHeight(-15);
				
				/* When a weather change occurs, each aircraft type needs to log a message, as seen in the example. */
				log("Its too cold!!");
				
				break;
			}
		}
		
		/* If an aircraft reaches height 0 or needs to go below it, the aircraft lands, unregisters from the weather tower and logs its current coordinates. */
		if (!Weather.SUN.equals(weather) && coordinates.isOnGround()) {
			logLanding();
			
			weatherTower.unregister(this);
		}
	}
	
	/* UML: +registerTower(weatherTower : WeatherTower) : void */
	@Override
	public void registerTower(WeatherTower weatherTower) {
		this.weatherTower = weatherTower;
	}
	
}