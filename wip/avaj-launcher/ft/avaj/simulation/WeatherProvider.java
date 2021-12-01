package ft.avaj.simulation;

import ft.avaj.vehicule.Coordinates;

public class WeatherProvider {
	
	/* UML: __-weatherProvider : WeatherProvider__ */
	private static final WeatherProvider weatherProvider = new WeatherProvider();
	
	/* UML: __-weather : string[]__ */
	private static final String[] weather = { /* There are 4 types of weather */
			Weather.SUN.name(),
			Weather.RAIN.name(),
			Weather.FOG.name(),
			Weather.SNOW.name(),
	};
	
	/* UML: -WeatherProvider() */
	private WeatherProvider() {
	}
	
	/* Each 3 dimensional point has its own weather. Feel free to use whatever generation algorithm you want, as long as it takes into account the point’s coordinates. */
	/* UML: +getCurrentWeather(coordinates : Coordinates) : string */
	public String getCurrentWeather(Coordinates coordinates) {
		return weather[coordinates.sum() % weather.length];
	}
	
	/* UML: __+getProvider() : WeatherProvider__ */
	public static WeatherProvider getProvider() {
		return weatherProvider;
	}
	
}