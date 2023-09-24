package ft.app.matcha.domain.tag;

import java.time.LocalDateTime;
import java.util.Optional;

import com.github.javafaker.Faker;

import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import lombok.RequiredArgsConstructor;
import spark.utils.StringUtils;

@RequiredArgsConstructor
public class TagService {
	
	private final TagRepository repository;

	public Optional<Tag> find(long id) {
		return repository.findById(id);
	}
	
	public Page<Tag> findAll(Pageable pageable) {
		return repository.findAll(pageable);
	}
	
	public Page<Tag> search(String query, Pageable pageable) {
		return repository.findAllByNameLike(query, pageable);
	}
	
	public Tag create(String name, String color) {
		final var formattedName = TagFormatter.format(name);
		
		return repository.findByName(formattedName)
			.orElseGet(() -> doCreate(formattedName, color));
	}
	
	private Tag doCreate(String formattedName, String color) {
		if (StringUtils.isBlank(color)) {
			color = Faker.instance().color().hex(true);
		}
		
		return repository.save(
			new Tag()
				.setName(formattedName)
				.setColor(color)
				.setCreatedAt(LocalDateTime.now())
		);
	}
	
}