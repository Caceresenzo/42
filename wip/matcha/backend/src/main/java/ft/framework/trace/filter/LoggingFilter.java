package ft.framework.trace.filter;

import java.time.Duration;
import java.util.Optional;

import ft.framework.mvc.filter.Filter;
import ft.framework.mvc.security.Authentication;
import ft.framework.mvc.security.AuthenticationFilter;
import lombok.extern.slf4j.Slf4j;
import spark.Request;
import spark.Response;

@Slf4j
public class LoggingFilter implements Filter {
	
	public static final String START_ATTRIBUTE = LoggingFilter.class.getSimpleName() + ".start";
	
	@Override
	public void preProcess(Request request, Response response) {
		final var start = System.nanoTime();
		
		request.attribute(START_ATTRIBUTE, start);
	}

	@Override
	public void postProcess(Request request, Response response) {
		final var end = System.nanoTime();
		final var start = request.<Long>attribute(START_ATTRIBUTE);
		
		final var duration = Duration.ofNanos(end - start);
		
		final var authentication = Optional.ofNullable(AuthenticationFilter.getAuthentication(request))
			.map(Authentication::getName)
			.orElse(null);
		
		log.info("{} {} - {} - {}", request.requestMethod(), request.pathInfo(), authentication, duration);
	}
	
}