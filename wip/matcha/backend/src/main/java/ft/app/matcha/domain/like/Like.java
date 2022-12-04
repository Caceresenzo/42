package ft.app.matcha.domain.like;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

import ft.app.matcha.domain.user.User;
import lombok.Data;
import lombok.experimental.Accessors;

@Entity
@Table
@Data
@Accessors(chain = true)
public class Like {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	private User user;
	
	@ManyToOne(optional = false)
	private User peer;
	
	@Column
	private LocalDateTime createdAt;
	
}