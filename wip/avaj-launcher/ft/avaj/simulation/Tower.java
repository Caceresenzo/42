package ft.avaj.simulation;

import java.util.ArrayList;
import java.util.List;

import ft.avaj.vehicule.Flyable;

public class Tower {
	
	private final List<Flyable> observers;
	
	public Tower() {
		this.observers = new ArrayList<>();
	}
	
	public void add(Flyable flyable) {
		ensureNotNull(flyable);
		
		observers.add(flyable);
	}
	
	public void remove(Flyable flyable) {
		ensureNotNull(flyable);
		
		observers.remove(flyable);
	}
	
	protected void conditionsChanged() {
		for (Flyable flyable : new ArrayList<>(observers)) {
			flyable.updateConditions();
		}
	}
	
	private void ensureNotNull(Flyable flyable) {
		if (flyable == null) {
			throw new IllegalArgumentException("flyable == null");
		}
	}
	
}