package ft.avaj.vehicule;

import ft.avaj.simulation.WeatherTower;

public interface Flyable {
	
	void updateConditions();
	
	void registerTower(WeatherTower weatherTower);
	
}