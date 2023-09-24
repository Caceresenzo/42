package ft.app.matcha.domain.notification;

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
public class Notification {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@Column(nullable = false)
	private Type type;
	
	@Column(nullable = false)
	private String content;
	
	@Column
	private String link;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private User user;
	
	@Column(nullable = false)
	private boolean read;
	
	@Column
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime readAt;
	
	@Column(nullable = false)
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime createdAt;
	
	public enum Type {
		
		WELCOME,
		LIKED,
		PROFILE_CHECKED,
		MESSAGE_RECEIVED,
		LIKED_BACK,
		UNLIKED;
	
	}
	
}