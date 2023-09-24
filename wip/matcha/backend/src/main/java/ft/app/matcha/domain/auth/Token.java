
package ft.app.matcha.domain.auth;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Index;
import javax.persistence.ManyToOne;
import javax.persistence.Table;
import javax.persistence.Transient;
import javax.persistence.UniqueConstraint;

import ft.app.matcha.domain.user.User;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table(indexes = {
	@Index(columnList = Token.Fields.type),
	@Index(columnList = Token.Fields.encoded),
}, uniqueConstraints = {
	@UniqueConstraint(columnNames = {
		Token.Fields.type,
		Token.Fields.encoded,
	}),
})
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Token {
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@Column(nullable = false)
	private Type type;
	
	@ManyToOne(optional = false)
	private User user;
	
	@Column(nullable = false, length = Short.MAX_VALUE)
	private String encoded;
	
	@Transient
	private String plain;

	@Column(length = 1024)
	private String extra;
	
	@Column(nullable = false)
	private LocalDateTime expireAt;
	
	@Column(nullable = false)
	private LocalDateTime createdAt;
	
	public void assertType(Type type) {
		if (!this.type.equals(type)) {
			throw new IllegalArgumentException("token is not a type " + type);
		}
	}
	
	@Getter
	@AllArgsConstructor
	public enum Type {
		
		CONFIRM(true),
		REFRESH(false),
		PASSWORD(true),
		EMAIL(true);
		
		private final boolean unique;
		
	}
	
}