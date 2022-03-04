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

#include <engine/model/Mesh.hpp>
#include <engine/model/MeshShader.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <stddef.h>

Mesh::Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<unsigned int> &indices, Mode mode) :
		m_vertices(vertices),
		m_indices(indices),
		m_mode(mode),
		m_vertex_buffer_array(NULL)
{
	try
	{
		m_vertex_buffer_array = new VertexArrayObject();
		m_vertex_buffer_array->bind();

		VertexBufferObject &element_buffer = *new VertexBufferObject(VertexBufferObject::ELEMENT_ARRAY, VertexBufferObject::STATIC_DRAW);
		m_vertex_buffer_array->add(element_buffer, true);

		element_buffer.bind();
		element_buffer.store(indices, false);

		VertexBufferObject &buffer_object = *new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
		m_vertex_buffer_array->add(buffer_object, true);

		buffer_object.bind();
		buffer_object.store(vertices, false);

		m_vertex_buffer_array->unbind();
	}
	catch (...)
	{
		if (m_vertex_buffer_array)
			delete m_vertex_buffer_array;
	}
}

Mesh::~Mesh()
{
	delete m_vertex_buffer_array;
}

void
Mesh::render(MeshShader &shader)
{
	m_vertex_buffer_array->bind(true);

	shader.positions.enable();
	shader.positions.link();

	glDrawElements(m_mode, m_indices.size(), GL_UNSIGNED_INT, NULL);

	m_vertex_buffer_array->unbind(true);

	shader.positions.disable();
}
