package ft.avaj.vehicule;

public class Coordinates {
	
	public static final int MIN_VALUE = 0;
	public static final int MAX_HEIGHT = 100;
	
	private int longitude;
	private int latitude;
	private int height;
	
	Coordinates(int longitude, int latitude, int height) {
		this.longitude = safeValue(longitude);
		this.latitude = safeValue(latitude);
		this.height = safeHeight(height);
	}
	
	public int getLongitude() {
		return longitude;
	}
	
	public void setLongitude(int longitude) {
		this.longitude = safeValue(longitude);
	}
	
	public void addLongitude(int value) {
		setLongitude(getLongitude() + value);
	}
	
	public int getLatitude() {
		return latitude;
	}
	
	public void setLatitude(int latitude) {
		this.latitude = safeValue(latitude);
	}
	
	public void addLatitude(int value) {
		setLatitude(getLatitude() + value);
	}
	
	public int getHeight() {
		return height;
	}
	
	public void setHeight(int height) {
		this.height = safeHeight(height);
	}
	
	public void addHeight(int value) {
		setHeight(getHeight() + value);
	}
	
	private static int safeValue(int value) {
		return Math.max(value, MIN_VALUE);
	}
	
	private static int safeHeight(int height) {
		return Math.min(safeValue(height), MAX_HEIGHT);
	}
	
	public boolean isOnGround() {
		return height == MIN_VALUE;
	}
	
	public int sum() {
		return longitude + latitude + height;
	}
	
}