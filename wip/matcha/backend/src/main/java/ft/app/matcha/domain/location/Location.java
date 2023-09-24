package ft.app.matcha.domain.location;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.UniqueConstraint;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.app.matcha.domain.user.User;
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table(uniqueConstraints = {
	@UniqueConstraint(columnNames = {
		Location.Fields.user
	})
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Location {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private User user;
	
	@Column(nullable = false)
	private boolean shared;
	
	@Column
	private Double latitude;
	
	@Column
	private Double longitude;
	
	@Column
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime updatedAt;
	
	public long getUserId() {
		return user.getId();
	}
	
}