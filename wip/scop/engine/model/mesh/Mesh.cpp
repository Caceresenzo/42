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

#include <engine/model/mesh/Mesh.hpp>
#include <engine/model/mesh/MeshShader.hpp>
#include <engine/shader/attribute/VectorAttribute.hpp>
#include <engine/shader/uniform/BooleanUniform.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>
#include <engine/vertex/VertexBufferObject.hpp>
#include <stddef.h>
#include <queue>
#include <utility>

Mesh::Mesh(const std::vector<Vector<3, float> > &vertices, const std::vector<Vector<2, float> > &textures, const std::vector<unsigned int> &indices, Mode mode) :
		m_vertices(vertices),
		m_textures(textures),
		m_indices(indices),
		m_mode(mode),
		m_vertex_buffer_array(NULL),
		m_texture(std::make_pair((Texture*)NULL, false))
{
	try
	{
		m_vertex_buffer_array = new VertexArrayObject();
		m_vertex_buffer_array->bind();

		VertexBufferObject &element_buffer = *new VertexBufferObject(VertexBufferObject::ELEMENT_ARRAY, VertexBufferObject::STATIC_DRAW);
		m_vertex_buffer_array->add(element_buffer, true);

		element_buffer.bind();
		element_buffer.store(indices, false);

		VertexBufferObject &vertex_buffer = *new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
		m_vertex_buffer_array->add(vertex_buffer, true);

		vertex_buffer.bind();
		vertex_buffer.store(vertices, false);

		if (!m_textures.empty())
		{
			VertexBufferObject &texture_buffer = *new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::STATIC_DRAW);
			m_vertex_buffer_array->add(texture_buffer, true);

			texture_buffer.bind();
			texture_buffer.store(textures, false);
		}

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

	if (m_texture.second)
		delete m_texture.first;
}

void
Mesh::set_texture(Texture &texture, bool auto_manage)
{
	m_texture = std::make_pair(&texture, auto_manage);
}

void
Mesh::remove_texture(void)
{
	m_texture = std::make_pair((Texture*)NULL, false);
}

void
Mesh::render(MeshShader &shader)
{
	m_vertex_buffer_array->bind(true);

	m_vertex_buffer_array->get(1).bind();
	shader.positions.link();
	shader.positions.enable();

	shader.use_texture.set(m_texture.first);

	if (!m_textures.empty() && m_texture.first)
	{
		m_vertex_buffer_array->get(2).bind();
		shader.texture_positions.link();
		shader.texture_positions.enable();

		Texture &texture = *m_texture.first;

		texture.set_active(0);
		texture.bind();
		shader.texture_sampler.set(0);
	}

	glDrawElements(m_mode, m_indices.size(), GL_UNSIGNED_INT, NULL);

	if (!m_textures.empty() && m_texture.first)
	{
		Texture &texture = *m_texture.first;

		texture.set_active(0);
		texture.unbind();
	}

	m_vertex_buffer_array->unbind(true);

	shader.positions.disable();
}
