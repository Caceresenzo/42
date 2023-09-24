package ft.app.matcha.domain.picture;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.UniqueConstraint;

import ft.app.matcha.domain.user.User;
import ft.framework.orm.annotation.OnDelete;
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table(name = "picture_defaults", uniqueConstraints = {
	@UniqueConstraint(columnNames = {
		DefaultPicture.Fields.user
	})
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class DefaultPicture {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	private User user;
	
	@ManyToOne(optional = false)
	@OnDelete(action = OnDelete.Action.CASCADE)
	private Picture picture;
	
	@Column(nullable = false)
	private LocalDateTime selectedAt;
	
}