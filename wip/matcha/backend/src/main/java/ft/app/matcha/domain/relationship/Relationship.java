package ft.app.matcha.domain.relationship;

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
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table(uniqueConstraints = {
	@UniqueConstraint(columnNames = {
		Relationship.Fields.user,
		Relationship.Fields.peer,
	})
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Relationship {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	private User user;
	
	@ManyToOne(optional = false)
	private User peer;
	
	@Column(nullable = false)
	private Type type;
	
	@Column(nullable = false)
	private LocalDateTime createdAt;
	
	public enum Type {
		
		LIKE,
		BLOCK;
	
	}
	
}