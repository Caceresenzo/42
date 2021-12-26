package ft.avaj.vehicule;

public class Coordinates {
	
	public static final int MIN_VALUE = 0;
	public static final int MAX_HEIGHT = 100;
	
	/* UML: -longitude : int */
	private int longitude;
	
	/* UML: -latitude : int */
	private int latitude;
	
	/* UML: -height : int */
	private int height;
	
	/* UML: ~Coordinates(longitude : int, latitude : int, height : int) */
	Coordinates(int longitude, int latitude, int height) {
		this.longitude = ensurePositiveOrZero(longitude);
		this.latitude = ensurePositiveOrZero(latitude);
		this.height = safeHeight(height, true);
	}
	
	/* UML: +getLongitude() */
	public int getLongitude() {
		return longitude;
	}
	
	public void setLongitude(int longitude) {
		if (isOnGround()) {
			return;
		}
		
		this.longitude = ensurePositiveOrZero(longitude);
	}
	
	public void addLongitude(int value) {
		setLongitude(getLongitude() + value);
	}
	
	/* UML: +getLatitude() */
	public int getLatitude() {
		return latitude;
	}
	
	public void setLatitude(int latitude) {
		if (isOnGround()) {
			return;
		}
		
		this.latitude = ensurePositiveOrZero(latitude);
	}
	
	public void addLatitude(int value) {
		setLatitude(getLatitude() + value);
	}
	
	/* UML: +getHeight() */
	public int getHeight() {
		return height;
	}
	
	public void setHeight(int height) {
		this.height = safeHeight(height, false);
	}
	
	public void addHeight(int value) {
		setHeight(getHeight() + value);
	}
	
	/* Coordinates are positive numbers. */
	private static int ensurePositiveOrZero(int value) {
		if (value < 0) {
			throw new IllegalArgumentException("< 0");
		}
		
		return value;
	}
	
	/* The height is in the 0-100 range. */
	private static int safeHeight(int height, boolean ensure) {
		int value;
		
		if (ensure) {
			value = ensurePositiveOrZero(height);
		} else {
			/* If an aircraft needs to pass the upper limit height it remains at 100. */
			value = Math.max(MIN_VALUE, height);
		}
		
		return Math.min(value, MAX_HEIGHT);
	}
	
	public boolean isOnGround() {
		return height == MIN_VALUE;
	}
	
	public int sum() {
		return longitude + latitude + height;
	}
	
	@Override
	public String toString() {
		return "LONGITUDE=" + longitude + " LATITUDE=" + latitude + " HEIGHT=" + height;
	}
	
}