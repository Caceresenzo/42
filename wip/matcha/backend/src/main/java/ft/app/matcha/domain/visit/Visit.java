package ft.app.matcha.domain.visit;

import java.time.LocalDate;
import java.time.LocalTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.UniqueConstraint;

import ft.app.matcha.domain.user.User;
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table(uniqueConstraints = {
	@UniqueConstraint(columnNames = {
		Visit.Fields.user,
		Visit.Fields.viewer,
		Visit.Fields.date
	})
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Visit {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	private User user;
	
	@ManyToOne
	private User viewer;
	
	@Column(nullable = false)
	private LocalDate date;
	
	@Column(nullable = false)
	private long times;
	
	@Column(nullable = false)
	private LocalTime firstAt;
	
	@Column(nullable = false)
	private LocalTime lastAt;
	
}