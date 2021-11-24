package ft.avaj.simulation;

import ft.avaj.vehicule.Coordinates;
import ft.avaj.vehicule.Flyable;

public class WeatherTower extends Tower {
	
	@Override
	public void register(Flyable flyable) {
		super.register(flyable);
		
		flyable.registerTower(this);
		
		says("%s registered to weather tower.", flyable);
	}
	
	@Override
	public void unregister(Flyable flyable) {
		super.unregister(flyable);
		
		flyable.registerTower(null);
		
		says("%s unregistered from weather tower.", flyable);
	}
	
	public String getWeather(Coordinates coordinates) {
		return WeatherProvider.getProvider().getCurrentWeather(coordinates);
	}
	
	void changeWeather() {
		conditionsChanged();
	}
	
	private void says(String format, Object... args) {
		System.out.println("Tower says: " + String.format(format, args));
	}
	
}