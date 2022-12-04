package ft.framework.swagger.part;

import java.lang.reflect.AnnotatedElement;
import java.lang.reflect.Type;
import java.util.Optional;

import io.swagger.models.Model;
import io.swagger.models.ModelImpl;
import io.swagger.models.properties.ObjectProperty;
import io.swagger.models.properties.Property;

public class ModelBuilder {
	
	public static Optional<Model> build(Type type) {
		return PropertyBuilder.build(type).map(ModelBuilder::convert);
	}
	
	public static Optional<Model> build(AnnotatedElement annotatedElement, String name, Type type) {
		return PropertyBuilder.build(annotatedElement, name, type).map(ModelBuilder::convert);
	}
	
	private static Model convert(Property property) {
		final var model = new ModelImpl();
		
		model.setTitle(property.getTitle());
		model.setType(property.getType());
		model.setFormat(property.getFormat());
		model.setName(property.getName());
		
		if (property instanceof ObjectProperty objectProperty) {
			model.setProperties(objectProperty.getProperties());
		}
		
		return model;
	}
	
}