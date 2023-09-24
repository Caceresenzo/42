package ft.framework.mvc.domain;

import java.util.Collections;
import java.util.List;
import java.util.function.Function;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Builder;
import lombok.Data;
import lombok.RequiredArgsConstructor;

@Data
@Builder
@RequiredArgsConstructor
public class Page<T> {
	
	private final List<T> content;
	private final long totalElements;
	
	@JsonIgnore
	private final Pageable pageable;
	
	public long getPageNumber() {
		return pageable.getPage();
	}
	
	public long getPageSize() {
		return pageable.getSize();
	}
	
	public long getTotalPages() {
		final var size = getPageSize();
		final var count = totalElements / size;
		
		return count + 1;
	}
	
	public boolean isFirst() {
		return pageable.getPage() == 0;
	}
	
	public boolean isLast() {
		return pageable.getPage() >= getTotalPages();
	}
	
	public <V> Page<V> map(Function<T, V> mapper) {
		return new Page<>(content.stream().map(mapper).toList(), totalElements, pageable);
	}
	
	public static <T> Page<T> empty(Pageable pageable) {
		return new Page<>(Collections.emptyList(), 0, pageable);
	}
	
}