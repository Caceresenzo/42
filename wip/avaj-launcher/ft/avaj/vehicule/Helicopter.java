package ft.avaj.vehicule;

import ft.avaj.simulation.WeatherTower;

public class Helicopter extends Aircraft implements Flyable {
	
	private WeatherTower weatherTower;
	
	Helicopter(String name, Coordinates coordinates) {
		super(name, coordinates);
	}
	
	@Override
	public void updateConditions() {
		switch (getCurrentWeather()) {
			case SUN: {
				coordinates.addLongitude(10);
				coordinates.addHeight(2);
				
				log("The view is clear!");
				
				break;
			}
			
			case RAIN: {
				coordinates.addLongitude(5);
				
				log("Avoiding rain.");
				
				break;
			}
			
			case FOG: {
				coordinates.addLongitude(1);
				
				log("Its getting difficult to see.");
				
				break;
			}
			
			case SNOW: {
				coordinates.addHeight(-12);
				
				log("The snow might be too dangerous!");
				
				if (coordinates.isOnGround()) {
					logLanding();
					
					weatherTower.remove(this);
				}
				
				break;
			}
		}
	}
	
	@Override
	public void registerTower(WeatherTower weatherTower) {
		this.weatherTower = weatherTower;
	}
	
}