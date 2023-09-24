package ft.app.matcha.domain.notification;

import org.apache.commons.lang3.tuple.Pair;

import ft.app.matcha.domain.message.Message;
import ft.app.matcha.domain.user.User;

public class NotificationFormatter {
	
	public static Pair<String, String> formatLiked(User user) {
		return Pair.of(
			"%s liked you!".formatted(user.getFirstName()),
			toUserLink(user)
		);
	}
	
	public static Pair<String, String> formatLikedBack(User user) {
		return Pair.of(
			"%s liked you back!".formatted(user.getFirstName()),
			toUserLink(user)
		);
	}
	
	public static Pair<String, String> formatUnliked(User user) {
		return Pair.of(
			"%s unliked you!".formatted(user.getFirstName()),
			toUserLink(user)
		);
	}
	
	public static Pair<String, String> formatMessageReceived(Message message) {
		final var user = message.getUser();
		
		return Pair.of(
			"%s sent you a message!".formatted(user.getFirstName()),
			"%s/messages".formatted(toUserLink(user))
		);
	}
	
	public static Pair<String, String> formatProfileChecked(User viewer) {
		return Pair.of(
			"%s viewed your profile!".formatted(viewer.getFirstName()),
			toUserLink(viewer)
		);
	}
	
	public static String toUserLink(User user) {
		return "/users/%s".formatted(user.getId());
	}
	
}