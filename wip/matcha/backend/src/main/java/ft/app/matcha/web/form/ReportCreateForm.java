package ft.app.matcha.web.form;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import ft.app.matcha.domain.report.Report;
import ft.framework.validation.constraint.annotation.Length;
import ft.framework.validation.constraint.annotation.NotBlank;
import ft.framework.validation.constraint.annotation.NotNull;
import lombok.Data;
import lombok.experimental.Accessors;

@Data
@Accessors(chain = true)
@JsonIgnoreProperties(ignoreUnknown = true)
public class ReportCreateForm {
	
	@NotBlank
	@Length(max = Report.MAX_REASON_LENGTH)
	private String reason;
	
	@NotNull
	private Long userId;
	
}