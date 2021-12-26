package ft.avaj.simulation;

import java.util.ArrayList;
import java.util.List;

import ft.avaj.vehicule.Flyable;

public class Tower {
	
	/* UML: -observers : Flyable* */
	private final List<Flyable> observers;
	
	public Tower() {
		this.observers = new ArrayList<>();
	}
	
	/* UML: +register(flyable : Flyable) : void */
	public void register(Flyable flyable) {
		ensureNotNull(flyable);
		
		observers.add(flyable);
	}
	
	/* UML: +unregister(flyable : Flyable) : void */
	public void unregister(Flyable flyable) {
		ensureNotNull(flyable);
		
		observers.remove(flyable);
	}
	
	/* UML: #conditionsChanged() : void */
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