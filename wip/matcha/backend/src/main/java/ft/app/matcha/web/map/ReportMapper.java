package ft.app.matcha.web.map;

import ft.app.matcha.domain.report.Report;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.web.dto.ReportDto;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class ReportMapper {
	
	private final UserMapper userMapper;
	
	public ReportDto toDto(Report report, User principal) {
		return new ReportDto()
			.setId(report.getId())
			.setReason(report.getReason())
			.setReporter(userMapper.toDto(report.getReporter(), principal))
			.setCreatedAt(report.getCreatedAt());
	}
	
}