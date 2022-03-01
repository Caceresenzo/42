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

Mesh::Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<unsigned int> &indices) :
		m_vertices(vertices),
		m_indices(indices),
		m_vertex_buffer_array(NULL)
{
	try
	{
		m_vertex_buffer_array = new VertexArrayObject();
		m_vertex_buffer_array->bind();

//		VertexBufferObject &element_buffer = *new VertexBufferObject(VertexBufferObject::ELEMENT_ARRAY, VertexBufferObject::STATIC_DRAW);
//		m_vertex_buffer_array->add(element_buffer, true);
//
//		element_buffer.bind();
//		element_buffer.store(indices, false);

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
//	std::cout << "bind" << std::endl << std::flush;
	m_vertex_buffer_array->bind();
	m_vertex_buffer_array->get(0).bind();
//	std::cout << "enable" << std::endl << std::flush;
	shader.positions.enable();
//	std::cout << "link" << std::endl << std::flush;
	shader.positions.link();

//	std::cout << "glDrawElements" << std::endl << std::flush;
//	std::cout << m_indices.size() << std::endl << std::flush;
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() * 3);
//	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_FLOAT, 0);
//	std::cout << "unbind" << std::endl << std::flush;
	m_vertex_buffer_array->unbind();

//	std::cout << "disable" << std::endl << std::flush;
	shader.positions.disable();
}
