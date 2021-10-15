package ft.avaj.vehicule;

import ft.avaj.simulation.Weather;
import ft.avaj.simulation.WeatherTower;

public class Baloon extends Aircraft implements Flyable {
	
	private WeatherTower weatherTower;
	
	Baloon(String name, Coordinates coordinates) {
		super(name, coordinates);
	}
	
	@Override
	public void updateConditions() {
		Weather weather = getCurrentWeather();
		
		switch (weather) {
			case SUN: {
				coordinates.addLongitude(2);
				coordinates.addHeight(4);
				
				log("I hope the air isn't too hot?");
				
				break;
			}
			
			case RAIN: {
				coordinates.addHeight(-5);
				
				log("Its wetting my baloon!");
				
				break;
			}
			
			case FOG: {
				coordinates.addHeight(-3);
				
				log("I can't see anything...");
				
				break;
			}
			
			case SNOW: {
				coordinates.addHeight(-15);
				
				log("Its too cold!!");
				
				break;
			}
		}
		
		if (!Weather.SUN.equals(weather) && coordinates.isOnGround()) {
			logLanding();
			
			weatherTower.remove(this);
		}
	}
	
	@Override
	public void registerTower(WeatherTower weatherTower) {
		this.weatherTower = weatherTower;
	}
	
}