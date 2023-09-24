package ft.app.matcha.web.map;

import ft.app.matcha.domain.relationship.Relationship;
import ft.app.matcha.domain.relationship.RelationshipService;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.web.dto.RelationshipDto;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class RelationshipMapper {
	
	private final RelationshipService relationshipService;
	
	public RelationshipDto toDto(User user, User peer) {
		if (user.getId() == peer.getId()) {
			return new RelationshipDto().setType(RelationshipDto.Type.YOURSELF);
		}
		
		final var relationship = relationshipService.find(user, peer).orElse(null);
		if (relationship == null) {
			return new RelationshipDto().setType(RelationshipDto.Type.STRANGER);
		}
		
		final var type = convertType(relationship.getType());
		final var mutual = relationshipService.isMutual(relationship);
		
		return new RelationshipDto(type, mutual, relationship.getCreatedAt());
	}
	
	public RelationshipDto.Type convertType(Relationship.Type type) {
		return switch (type) {
			case LIKE -> RelationshipDto.Type.LIKE;
			case BLOCK -> RelationshipDto.Type.BLOCK;
			default -> throw new IllegalArgumentException("Unexpected value: " + type);
		};
	}
	
}