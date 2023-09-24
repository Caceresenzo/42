package ft.framework.mvc.security;

import java.util.List;

import lombok.Builder;
import lombok.NonNull;
import lombok.Singular;
import spark.Request;
import spark.Response;

@Builder
public class CompositeAuthenticationFilter extends AuthenticationFilter {
	
	@Singular
	private final List<@NonNull AuthenticationFilter> filters;
	
	@Override
	public Authentication authenticate(Request request, Response response) {
		for (final var filter : filters) {
			final var authentication = filter.authenticate(request, response);
			
			if (authentication != null) {
				return authentication;
			}
		}
		
		return null;
	}
	
}