package ft.framework.mvc.domain;

import lombok.Builder;
import lombok.Data;
import lombok.RequiredArgsConstructor;

@Data
@Builder
@RequiredArgsConstructor
public class Pageable {
	
	private final long size;
	private final long page;
	
}