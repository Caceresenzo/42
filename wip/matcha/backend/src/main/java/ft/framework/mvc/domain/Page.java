package ft.framework.mvc.domain;

import java.util.List;

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
		
		if (count % size == 0) {
			return count;
		} else {
			return count + 1;
		}
	}
	
	public boolean isFirst() {
		return pageable.getPage() == 0;
	}
	
	public boolean isLast() {
		return pageable.getPage() >= getTotalPages();
	}
	
}