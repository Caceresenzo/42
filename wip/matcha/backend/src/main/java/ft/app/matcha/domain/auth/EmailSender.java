package ft.app.matcha.domain.auth;

import java.io.StringWriter;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.regex.Pattern;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

import org.apache.commons.lang3.StringUtils;

import freemarker.template.Configuration;
import freemarker.template.Template;
import freemarker.template.TemplateExceptionHandler;
import ft.app.matcha.configuration.EmailConfigurationProperties;
import ft.app.matcha.configuration.UrlConfigurationProperties;
import ft.framework.util.MediaTypes;
import lombok.RequiredArgsConstructor;
import lombok.SneakyThrows;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@RequiredArgsConstructor
public class EmailSender {
	
	public static final Pattern TITLE_PATTERN = Pattern.compile("<title>(.+?)</title>");
	
	private final EmailConfigurationProperties emailProperties;
	private final InternetAddress from;
	private final Configuration freemarkerConfiguration;
	private final Urls urls;
	
	@SneakyThrows
	public EmailSender(EmailConfigurationProperties emailProperties, UrlConfigurationProperties urlProperties) {
		this.emailProperties = emailProperties;
		this.from = new InternetAddress(emailProperties.getSender());
		
		this.freemarkerConfiguration = new Configuration(Configuration.VERSION_2_3_29);
		this.freemarkerConfiguration.setClassForTemplateLoading(this.getClass(), "/");
		this.freemarkerConfiguration.setDefaultEncoding("UTF-8");
		this.freemarkerConfiguration.setTemplateExceptionHandler(TemplateExceptionHandler.RETHROW_HANDLER);
		this.freemarkerConfiguration.setLogTemplateExceptions(false);
		this.freemarkerConfiguration.setWrapUncheckedExceptions(true);
		this.freemarkerConfiguration.setFallbackOnNullLoopVariable(false);
		
		this.urls = createUrls(urlProperties);
	}
	
	public boolean sendConfirmationEmail(Token token) {
		token.assertType(Token.Type.CONFIRM);
		
		final var user = token.getUser();
		final var plain = getPlain(token);
		
		final var url = urls.confirmEmail().formatted(plain);
		
		final var properties = Map.of(
			"url", url,
			"firstName", user.getFirstName(),
			"expireAt", formatDate(token.getExpireAt())
		);
		
		return sendEmail("confirm", user.getEmail(), properties);
	}
	
	public boolean sendPasswordResetEmail(Token token) {
		token.assertType(Token.Type.PASSWORD);
		
		final var user = token.getUser();
		final var plain = getPlain(token);
		
		final var url = urls.changePassword().formatted(plain);
		
		final var properties = Map.of(
			"url", url,
			"firstName", user.getFirstName(),
			"expireAt", formatDate(token.getExpireAt())
		);
		
		return sendEmail("forgot", user.getEmail(), properties);
	}
	
	public boolean sendChangeEmail(Token token, String newEmail) {
		token.assertType(Token.Type.EMAIL);
		
		final var user = token.getUser();
		final var plain = getPlain(token);
		
		final var url = urls.changeEmail().formatted(plain);
		
		final var properties = Map.of(
			"url", url,
			"firstName", user.getFirstName(),
			"newEmail", newEmail,
			"expireAt", formatDate(token.getExpireAt())
		);
		
		return sendEmail("new-email", newEmail, properties);
	}
	
	public boolean sendEmail(String templateName, String email, Map<?, ?> properties) {
		final var template = getTemplate(templateName);
		final var rendered = render(template, properties);
		
		return sendEmail(rendered, templateName, email);
	}
	
	public boolean sendEmail(String html, String templateName, String email) {
		try {
			final var session = getSession();
			final var message = new MimeMessage(session);
			
			log.info("Sending email template={} to={}", templateName, email);
			
			message.setFrom(from);
			message.addRecipient(Message.RecipientType.TO, new InternetAddress(email));
			message.setSubject(extractSubject(html).orElse(emailProperties.getDefaultSubject()));
			message.setContent(html, MediaTypes.HTML);
			
			Transport.send(message);
		} catch (MessagingException exception) {
			log.error("Could not send email", exception);
			return false;
		}
		
		return false;
	}
	
	@SneakyThrows
	public String render(Template template, Map<?, ?> properties) {
		final var writter = new StringWriter();
		
		template.process(properties, writter);
		
		return writter.getBuffer().toString();
	}
	
	@SneakyThrows
	public Template getTemplate(String name) {
		return freemarkerConfiguration.getTemplate("/email/%s.ftlh".formatted(name));
	}
	
	public Session getSession() {
		final var properties = System.getProperties();
		properties.put("mail.smtp.host", emailProperties.getHost());
		properties.put("mail.smtp.port", emailProperties.getPort());
		properties.put("mail.smtp.ssl.enable", emailProperties.isSsl());
		properties.put("mail.smtp.auth", emailProperties.isAuth());
		properties.put("mail.debug", emailProperties.isDebug());
		
		if (StringUtils.isNotEmpty(emailProperties.getAuthEmail())) {
			return Session.getInstance(properties, new javax.mail.Authenticator() {
				
				@Override
				protected PasswordAuthentication getPasswordAuthentication() {
					return new PasswordAuthentication(emailProperties.getAuthEmail(), emailProperties.getAuthPassword());
				}
				
			});
		}
		
		return Session.getInstance(properties, null);
	}
	
	public static String getPlain(Token token) {
		return Objects.requireNonNull(token.getPlain(), "token.plain is null");
	}
	
	public static String formatDate(LocalDateTime dateTime) {
		return dateTime.atZone(ZoneId.systemDefault()).format(DateTimeFormatter.ofLocalizedDateTime(FormatStyle.FULL));
	}
	
	public static Optional<String> extractSubject(String html) {
		final var matcher = TITLE_PATTERN.matcher(html);
		
		if (!matcher.find()) {
			return Optional.empty();
		}
		
		return Optional.of(matcher.group(1));
	}
	
	public static Urls createUrls(UrlConfigurationProperties properties) {
		var base = properties.getBase();
		if (StringUtils.isBlank(base)) {
			base = "";
		}
		
		return new Urls(
			toUrl(base, properties.getConfirmEmail()),
			toUrl(base, properties.getChangePassword()),
			toUrl(base, properties.getChangeEmail())
		);
	}
	
	public static String toUrl(String base, String format) {
		return format
			.replace("{base}", base)
			.replace("{token}", "%s");
	}
	
	public record Urls(
		String confirmEmail,
		String changePassword,
		String changeEmail
	) {}
	
}