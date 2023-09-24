package ft.app.matcha.domain.tag;

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
		UserTag.Fields.user,
		UserTag.Fields.tag,
	})
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class UserTag {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private User user;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private Tag tag;
	
	@Column(nullable = false)
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime createdAt;
	
	public long getUserId() {
		return user.getId();
	}
	
	public long getTagId() {
		return tag.getId();
	}
	
}