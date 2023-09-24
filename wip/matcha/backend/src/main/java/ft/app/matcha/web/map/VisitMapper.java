package ft.app.matcha.web.map;

import ft.app.matcha.domain.user.User;
import ft.app.matcha.domain.visit.Visit;
import ft.app.matcha.web.dto.VisitDto;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class VisitMapper {
	
	private final UserMapper userMapper;
	
	public VisitDto toDto(Visit visit, User principal) {
		final var viewer = visit.getViewer();
		
		return new VisitDto()
			.setId(visit.getId())
			.setUser(viewer != null
				? userMapper.toDto(viewer, principal)
				: null)
			.setDate(visit.getDate())
			.setTimes(visit.getTimes())
			.setFirstAt(visit.getFirstAt())
			.setLastAt(visit.getLastAt());
	}
	
}