package ft.framework.orm.repository;

import java.util.List;
import java.util.Optional;

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
		final var predicate = builder.equals(entity.getTable().getIdColumn(), id);
		
		return findBy(predicate);
	}
	
	public T getById(ID id) {
		return findById(id).orElse(null);
	}
	
	public List<T> findAll() {
		return entityManager.findAll(entity);
	}
	
	public T save(T instance) {
		return entityManager.persist(instance);
	}
	
	public T insert(T instance) {
		return entityManager.insert(instance);
	}
	
	public T update(T instance) {
		return entityManager.update(instance).getInstance();
	}
	
	protected Optional<T> findBy(Predicate<T> predicate) {
		return entityManager.findBy(entity, predicate);
	}
	
	protected List<T> findAllBy(Predicate<T> predicate) {
		return entityManager.findAllBy(entity, predicate);
	}
	
}