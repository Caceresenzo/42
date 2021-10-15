package ft.avaj.simulation;

import ft.avaj.vehicule.Coordinates;
import ft.avaj.vehicule.Flyable;

public class WeatherTower extends Tower {
	
	@Override
	public void add(Flyable flyable) {
		super.add(flyable);
		
		flyable.registerTower(this);
		
		says("%s registered to weather tower.", flyable);
	}
	
	@Override
	public void remove(Flyable flyable) {
		super.remove(flyable);
		
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