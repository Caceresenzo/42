package ft.framework.mvc.domain;

import ft.framework.validation.constraint.annotation.Positive;
import ft.framework.validation.constraint.annotation.PositiveOrZero;
import lombok.Builder;
import lombok.Data;
import lombok.RequiredArgsConstructor;

@Data
@Builder
@RequiredArgsConstructor
public class Pageable {
	
	@Positive
	private final long size;

	@PositiveOrZero
	private final long page;
	
	private final Sort sort;
	
}