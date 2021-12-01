package ft.avaj.vehicule;

import ft.avaj.simulation.WeatherTower;

public interface Flyable {
	
	/* UML: +updateConditions() : void */
	void updateConditions();
	
	/* UML: +registerTower(WeatherTower : WeatherTower) : void */
	void registerTower(WeatherTower weatherTower);
	
}