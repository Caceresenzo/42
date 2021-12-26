package ft.avaj.simulation;

import ft.avaj.vehicule.Coordinates;
import ft.avaj.vehicule.Flyable;

public class WeatherTower extends Tower {
	
	@Override
	public void register(Flyable flyable) {
		super.register(flyable);
		
		flyable.registerTower(this);
		
		/* Each time an aircraft registers or unregisters to/from the weather tower, a message will be logged. */
		says("%s registered to weather tower.", flyable);
	}
	
	@Override
	public void unregister(Flyable flyable) {
		super.unregister(flyable);
		
		flyable.registerTower(null);
		
		/* Each time an aircraft registers or unregisters to/from the weather tower, a message will be logged. */
		says("%s unregistered from weather tower.", flyable);
	}
	
	/* UML: +getWeather(coordinates : Coordinates) : String */
	public String getWeather(Coordinates coordinates) {
		return WeatherProvider.getProvider().getCurrentWeather(coordinates);
	}
	
	/* UML: ~changeWeather() : void */
	void changeWeather() {
		conditionsChanged();
	}
	
	private void says(String format, Object... args) {
		System.out.println("Tower says: " + String.format(format, args));
	}
	
}