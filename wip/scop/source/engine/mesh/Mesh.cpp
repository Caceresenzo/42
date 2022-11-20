/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:40:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 20:40:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/mesh/Mesh.hpp>
#include <engine/mesh/Vertex.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <lang/Math.hpp>
#include <stddef.h>
#include <iterator>
#include <limits>
#include <queue>
#include <utility>

Mesh::Mesh(const std::vector<Vertex<3> > &vertices, const std::vector<unsigned int> &indices, Mode mode) :
	vertices(vertices),
	indices(indices),
	mode(mode),
	vertex_array_object(*new VertexArrayObject()),
	vertex_buffer_object(*new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW)),
	element_buffer_object(*new VertexBufferObject(VertexBufferObject::ELEMENT_ARRAY, VertexBufferObject::STATIC_DRAW))
{
	vertex_array_object->add(vertex_buffer_object);
	vertex_buffer_object->store(vertices);

	vertex_array_object->add(element_buffer_object);
	element_buffer_object->store(indices);
}

Mesh::~Mesh()
{
}

void
Mesh::align(Vector<3, float> center)
{
	if (center == Vector<3, float>::ZERO)
		return;

	typedef std::vector<Vertex<3> >::iterator iterator;
	for (iterator it = vertices.begin(); it < vertices.end(); ++it)
		it->position -= center;

	vertex_buffer_object->store(vertices);
}

BoundingBox<3, float>
Mesh::compute_bounding_box() const
{
	if (vertices.empty())
		return (BoundingBox<3, float>(0, 0));

	Vector<3, float> lower(std::numeric_limits<float>::max());
	Vector<3, float> higher(std::numeric_limits<float>::min());

	typedef std::vector<Vertex<3> >::const_iterator iterator;
	for (iterator it = vertices.begin(); it < vertices.end(); ++it)
	{
		const Vector<3, float> &vector = it->position;

		lower.x = Math::min(lower.x, vector.x);
		lower.y = Math::min(lower.y, vector.y);
		lower.z = Math::min(lower.z, vector.z);

		higher.x = Math::max(higher.x, vector.x);
		higher.y = Math::max(higher.y, vector.y);
		higher.z = Math::max(higher.z, vector.z);
	}

	return (BoundingBox<3, float>(lower, higher));
}
