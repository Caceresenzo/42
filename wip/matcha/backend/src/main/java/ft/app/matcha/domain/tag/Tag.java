package ft.app.matcha.domain.tag;

import java.time.LocalDateTime;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

import lombok.Data;
import lombok.experimental.Accessors;
import lombok.experimental.FieldNameConstants;

@Entity
@Table
@Data
@Accessors(chain = true)
@FieldNameConstants
public class Tag {
	
	public static final int MAX_NAME_LENGTH = 48;
	public static final int MAX_COLOR_LENGTH = 24;
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private long id;
	
	@Column(nullable = false, unique = true)
	private String name;
	
	@Column
	private String color;
	
	@Column(nullable = false)
	private LocalDateTime createdAt;
	
}