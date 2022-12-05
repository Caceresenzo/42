package ft.app.matcha.domain.auth;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.Transient;

import ft.app.matcha.domain.user.User;
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table
@Data
@Accessors(chain = true)
@FieldNameConstants
public class RefreshToken {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@ManyToOne(optional = false)
	private User user;
	
	@Column(nullable = false, length = Short.MAX_VALUE, unique = true)
	private String encoded;
	
	@Transient
	private String plain;
	
	@Column(nullable = false)
	private LocalDateTime expireAt;
	
	@Column(nullable = false)
	private LocalDateTime createdAt;
	
}