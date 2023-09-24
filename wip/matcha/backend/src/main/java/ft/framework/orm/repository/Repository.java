package ft.framework.orm.repository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import ft.framework.mvc.domain.Page;
import ft.framework.mvc.domain.Pageable;
import ft.framework.mvc.domain.Sort;
import ft.framework.orm.EntityManager;
import ft.framework.orm.mapping.Entity;
import ft.framework.orm.predicate.Predicate;
import ft.framework.orm.predicate.PredicateBuilder;

public class Repository<T, ID> {
	
	protected final EntityManager entityManager;
	protected final Entity<T> entity;
	
	protected final PredicateBuilder<T> builder;
	
	public Repository(EntityManager entityManager, Class<T> clazz) {
		this.entityManager = entityManager;
		this.entity = entityManager.getEntity(clazz);
		
		this.builder = new PredicateBuilder<>(entity);
	}
	
	public Optional<T> findById(ID id) {
		return entityManager.findById(entity, id);
	}
	
	public T getById(ID id) {
		return findById(id).orElse(null);
	}
	
	public List<T> findAll() {
		return findAllBy(null);
	}
	
	public Page<T> findAll(Pageable pageable) {
		return findAllBy(null, pageable);
	}
	
	public T save(T instance) {
		return entityManager.persist(instance);
	}
	
	public List<T> saveAll(Iterable<T> iterable) {
		final var saved = new ArrayList<T>();
		
		for (T instance : iterable) {
			saved.add(save(instance));
		}
		
		return saved;
	}
	
	public T insert(T instance) {
		return entityManager.insert(instance);
	}
	
	public T update(T instance) {
		return entityManager.update(instance).getInstance();
	}
	
	public boolean delete(T instance) {
		return entityManager.delete(instance);
	}
	
	protected boolean existsBy(Predicate<T> predicate) {
		return entityManager.existsBy(entity, predicate);
	}
	
	protected Optional<T> findBy(Predicate<T> predicate) {
		return entityManager.findBy(entity, predicate);
	}
	
	protected Optional<T> findFirstBy(Predicate<T> predicate) {
		final var pageable = new Pageable(1, 0, Sort.UNSORTED);
		final var page = entityManager.findAllBy(entity, predicate, pageable);
		
		return page.getContent().stream().findFirst();
	}
	
	// protected Optional<T> findLastBy(Predicate<T> predicate) {
	// final var reverseId = new Sort(
	// Sort.Order.builder()
	// .descending()
	// .property(entity.getTable()
	// .getIdColumn()
	// .getField()
	// .getName())
	// .build()
	// );
	//
	// final var pageable = new Pageable(1, 0, reverseId);
	// final var page = entityManager.findAllBy(entity, predicate, pageable);
	//
	// return page.getContent().stream().findFirst();
	// }
	
	protected List<T> findAllBy(Predicate<T> predicate) {
		return entityManager.findAllBy(entity, predicate);
	}
	
	protected Page<T> findAllBy(Predicate<T> predicate, Pageable pageable) {
		return entityManager.findAllBy(entity, predicate, pageable);
	}
	
	protected long deleteAllBy(Predicate<T> predicate) {
		return entityManager.deleteAllBy(entity, predicate);
	}
	
	protected long countBy(Predicate<T> predicate) {
		return entityManager.countBy(entity, predicate);
	}
	
}