package ft.avaj.vehicule;

import java.lang.reflect.Constructor;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.TreeMap;

public class AircraftFactory {
	
	private static final Map<String, Class<? extends Flyable>> flyableClasses;
	static {
		flyableClasses = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
		
		flyableClasses.put(Helicopter.class.getSimpleName(), Helicopter.class);
		flyableClasses.put(JetPlane.class.getSimpleName(), JetPlane.class);
		flyableClasses.put(Baloon.class.getSimpleName(), Baloon.class);
	}
	
	public static Class<? extends Flyable> getClassByType(String type) {
		Class<? extends Flyable> clazz = flyableClasses.get(type);
		
		if (clazz == null) {
			throw new NoSuchElementException("unknown type: " + type);
		}
		
		return clazz;
	}
	
	public static Coordinates newCoordinates(int longitude, int latitude, int height) {
		return new Coordinates(longitude, latitude, height);
	}
	
	/* UML: __+newAircraft(type : string, name : string, longitude : int, latitude : int, height : int) : Flyable__ */
	public static Flyable newAircraft(String type, String name, int longitude, int latitude, int height) {
		Coordinates coordinates = newCoordinates(longitude, latitude, height);
		
		Class<? extends Flyable> clazz = getClassByType(type);
		
		try {
			Constructor<? extends Flyable> constructor = clazz.getDeclaredConstructor(String.class, Coordinates.class);
			
			return constructor.newInstance(name, coordinates);
		} catch (Exception exception) {
			throw new IllegalStateException("could not instanciate flyable object", exception);
		}
	}
	
}