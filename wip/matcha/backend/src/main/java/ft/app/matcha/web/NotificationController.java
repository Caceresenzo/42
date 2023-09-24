package ft.app.matcha.web;

import java.time.LocalDateTime;
import java.util.Optional;

import ft.app.matcha.domain.notification.Notification;
import ft.app.matcha.domain.notification.NotificationService;
import ft.app.matcha.domain.notification.exception.InvalidNotificationOwnerException;
import ft.app.matcha.domain.notification.exception.NotificationNotFoundException;
import ft.app.matcha.domain.user.User;
import ft.app.matcha.web.form.NotificationPatchForm;
import ft.framework.mvc.annotation.Authenticated;
import ft.framework.mvc.annotation.Body;
import ft.framework.mvc.annotation.Controller;
import ft.framework.mvc.annotation.GetMapping;
import ft.framework.mvc.annotation.PatchMapping;
import ft.framework.mvc.annotation.Principal;
import ft.framework.mvc.annotation.Query;
import ft.framework.mvc.annotation.RequestMapping;
import ft.framework.mvc.annotation.Variable;
import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.swagger.annotation.ApiOperation;
import ft.framework.validation.annotation.Valid;
import lombok.RequiredArgsConstructor;

@Controller
@RequestMapping(path = "/notifications")
@RequiredArgsConstructor
public class NotificationController {
	
	private final NotificationService notificationService;
	
	@Authenticated
	@GetMapping
	@ApiOperation(summary = "List received notifications.")
	public Page<Notification> list(
		Pageable pageable,
		@Query(required = false) boolean includeAll,
		@Principal User currentUser
	) {
		return notificationService.findAll(currentUser, includeAll, pageable);
	}
	
	@Authenticated
	@GetMapping(path = "{notificationId}")
	@ApiOperation(summary = "Show a notification.")
	public Notification show(
		@Variable long notificationId,
		@Principal User currentUser
	) {
		final var notification = notificationService.find(notificationId)
			.orElseThrow(() -> new NotificationNotFoundException(notificationId));
		
		if (notification.getUser().getId() != currentUser.getId()) {
			throw new InvalidNotificationOwnerException(notificationId);
		}
		
		return notification;
	}
	
	@Authenticated
	@PatchMapping(path = "{notificationId}")
	@ApiOperation(summary = "Update a notification.")
	public Notification patch(
		@Variable long notificationId,
		@Body @Valid NotificationPatchForm form,
		@Principal User currentUser
	) {
		final var notification = show(notificationId, currentUser);
		
		Optional.ofNullable(form.getRead()).ifPresent((read) -> {
			notification.setRead(read);
			notification.setReadAt(read ? LocalDateTime.now() : null);
		});
		
		return notificationService.save(notification);
	}
	
}