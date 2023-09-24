package ft.framework.mvc.domain;

import java.util.Collections;
import java.util.List;
import java.util.Optional;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.Getter;
import lombok.NonNull;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Data
public class Sort {
	
	public static final Sort UNSORTED = new Sort(Collections.emptyList());
	
	@NonNull
	private final List<Order> orders;
	
	public Sort(Order order) {
		this(Collections.singletonList(order));
	}
	
	public boolean isEmpty() {
		return orders.isEmpty();
	}
	
	@Builder
	@Data
	public static class Order {
		
		@Builder.Default
		@NonNull
		private final Direction direction = Direction.ASCENDING;
		
		@NonNull
		private final String property;
		
		public static class OrderBuilder {
			
			public OrderBuilder descending() {
				return direction(Direction.DESCENDING);
			}
			
		}
		
	}
	
	@AllArgsConstructor
	@Getter
	public enum Direction {
		
		ASCENDING("ASC"),
		DESCENDING("DESC");
		
		private final String shortName;
		
		public static Optional<Direction> parse(String input) {
			for (final var direction : Direction.values()) {
				if (direction.getShortName().equalsIgnoreCase(input)) {
					return Optional.of(direction);
				}
			}
			
			return Optional.empty();
		}
		
	}
	
}