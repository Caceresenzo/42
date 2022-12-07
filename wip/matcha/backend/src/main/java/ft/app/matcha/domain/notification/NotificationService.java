package ft.app.matcha.domain.notification;

import java.time.LocalDateTime;

import ft.app.matcha.domain.auth.event.RegisterEvent;
import ft.framework.event.annotation.EventListener;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
public class NotificationService {
	
	private final NotificationRepository repository;
	
	@EventListener
	public void onRegister(RegisterEvent event) {
		final var user = event.getUser();
		
		repository.save(new Notification()
			.setUser(user)
			.setContent("Welcome!")
			.setCreatedAt(LocalDateTime.now())
		);
	}
	
}