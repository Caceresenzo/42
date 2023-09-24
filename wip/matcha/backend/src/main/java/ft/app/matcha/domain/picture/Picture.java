package ft.app.matcha.domain.picture;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.app.matcha.domain.user.User;
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Picture {
	
	public static final int MAX_DESCRIPTION_LENGTH = 4000;
	public static final int MAX_PATH_LENGTH = 2000;
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private User user;
	
	@Column(nullable = false, length = MAX_PATH_LENGTH)
	@JsonIgnore
	private String path;
	
	@Column(length = MAX_DESCRIPTION_LENGTH)
	private String description;
	
	@Column(nullable = false)
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime createdAt;
	
	public long getUserId() {
		return user.getId();
	}
	
}