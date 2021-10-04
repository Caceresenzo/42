package ft.avaj.vehicule;

public class Coordinates {
	
	public static final int MIN_VALUE = 0;
	public static final int MAX_HEIGHT = 100;
	
	private int longitude;
	private int latitude;
	private int height;
	
	Coordinates(int longitude, int latitude, int height) {
		this.longitude = ensurePositiveOrZero(longitude);
		this.latitude = ensurePositiveOrZero(latitude);
		this.height = safeHeight(height, true);
	}
	
	public int getLongitude() {
		return longitude;
	}
	
	public void setLongitude(int longitude) {
		this.longitude = ensurePositiveOrZero(longitude);
	}
	
	public void addLongitude(int value) {
		setLongitude(getLongitude() + value);
	}
	
	public int getLatitude() {
		return latitude;
	}
	
	public void setLatitude(int latitude) {
		this.latitude = ensurePositiveOrZero(latitude);
	}
	
	public void addLatitude(int value) {
		setLatitude(getLatitude() + value);
	}
	
	public int getHeight() {
		return height;
	}
	
	public void setHeight(int height) {
		this.height = safeHeight(height, false);
	}
	
	public void addHeight(int value) {
		setHeight(getHeight() + value);
	}
	
	private static int ensurePositiveOrZero(int value) {
		if (value < 0) {
			throw new IllegalArgumentException("< 0");
		}
		
		return value;
	}
	
	private static int safeHeight(int height, boolean ensure) {
		int value;
		
		if (ensure) {
			value = ensurePositiveOrZero(height);
		} else {
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
	
}