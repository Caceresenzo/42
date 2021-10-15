package ft.avaj.vehicule;

import ft.avaj.simulation.WeatherTower;

public class JetPlane extends Aircraft implements Flyable {
	
	private WeatherTower weatherTower;
	
	JetPlane(String name, Coordinates coordinates) {
		super(name, coordinates);
	}
	
	@Override
	public void updateConditions() {
		switch (getCurrentWeather(weatherTower)) {
			case SUN: {
				coordinates.addLatitude(10);
				coordinates.addHeight(2);
				
				log("Tango, going faster!");
				
				break;
			}
			
			case RAIN: {
				coordinates.addLatitude(5);
				
				log("Turning to avoid rain.");
				
				break;
			}
			
			case FOG: {
				coordinates.addLatitude(1);
				
				log("Turning to avoid fog.");
				
				break;
			}
			
			case SNOW: {
				coordinates.addHeight(-7);
				
				log("Snow obscure view, going lower.");
				
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