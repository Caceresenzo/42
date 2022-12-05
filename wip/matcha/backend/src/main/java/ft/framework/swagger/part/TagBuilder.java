package ft.framework.swagger.part;

import java.util.Collections;
import java.util.Objects;
import java.util.Optional;

import ft.framework.mvc.mapping.Route;
import io.swagger.v3.oas.models.OpenAPI;
import io.swagger.v3.oas.models.tags.Tag;
import spark.utils.StringUtils;

public class TagBuilder {
	
	public static Optional<Tag> build(OpenAPI swagger, Route route) {
		final var container = route.getContainer();
		final var name = container.getClass()
			.getSimpleName()
			.replaceAll("(?:Rest)?Controller$", "");
		
		if (StringUtils.isBlank(name)) {
			return Optional.empty();
		}
		
		final var tag = getOrCreate(swagger, name);
		swagger.addTagsItem(tag);
		
		return Optional.of(tag);
	}
	
	public static Tag getOrCreate(OpenAPI swagger, String name) {
		return Optional.ofNullable(swagger.getTags())
			.orElse(Collections.emptyList())
			.stream()
			.filter((tag) -> Objects.equals(tag.getName(), name))
			.findFirst()
			.orElseGet(() -> new Tag().name(name));
	}
	
}