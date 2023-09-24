package ft.app.matcha.domain.message;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Index;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonIgnore;

import ft.app.matcha.domain.user.User;
import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table(indexes = {
	@Index(columnList = Message.Fields.user + "," + Message.Fields.peer)
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Message {
	
	public static final int MAX_CONTENT_LENGTH = 280;
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@Column(nullable = false, length = MAX_CONTENT_LENGTH)
	private String content;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private User user;
	
	@ManyToOne(optional = false)
	@JsonIgnore
	private User peer;
	
	@Column(nullable = false)
	@JsonFormat(shape = JsonFormat.Shape.STRING)
	private LocalDateTime createdAt;
	
	public long getUserId() {
		return user.getId();
	}
	
	public long getPeerId() {
		return peer.getId();
	}
	
}