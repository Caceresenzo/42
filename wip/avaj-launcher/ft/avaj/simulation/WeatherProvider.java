package ft.avaj.simulation;

import ft.avaj.vehicule.Coordinates;

public class WeatherProvider {
	
	private static final WeatherProvider weatherProvider = new WeatherProvider();
	
	private final String[] weather;
	
	private WeatherProvider() {
		this.weather = new String[] {
				Weather.SUN.name(),
				Weather.RAIN.name(),
				Weather.FOG.name(),
				Weather.SNOW.name(),
		};
	}
	
	public String getCurrentWeather(Coordinates coordinates) {
		return weather[coordinates.sum() % weather.length];
	}
	
	public static WeatherProvider getProvider() {
		return weatherProvider;
	}
	
}