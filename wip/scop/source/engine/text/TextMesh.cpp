/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Text.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:24:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/25 12:24:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/text/TextMesh.hpp>
#include <stddef.h>
#include <vector>

TextMesh::TextMesh(const std::string &initial, const Vector<2, float> &position, float size) :
	m_value(initial),
	m_position(position),
	m_size(size),
	m_invalidated(true),
	m_vertex_array(),
	m_vertex_buffer(VertexBufferObject::ARRAY, VertexBufferObject::DYNAMIC_DRAW),
	m_uv_buffer(VertexBufferObject::ARRAY, VertexBufferObject::DYNAMIC_DRAW)
{
	m_vertex_array.add(m_vertex_buffer, false);
	m_vertex_array.add(m_uv_buffer, false);
}

TextMesh::~TextMesh()
{
}

void
TextMesh::invalidate()
{
	m_invalidated = true;
}

void
TextMesh::build()
{
	std::vector<Vector<2, float> > vertices;
	std::vector<Vector<2, float> > uvs;

	size_t estimated = m_value.length() * (3 + 3);
	vertices.reserve(estimated);
	uvs.reserve(estimated);

	Vector<2, int> screen(0, 0);

	for (size_t index = 0; index < m_value.length(); index++)
		if (m_value[index] == '\n')
			screen.y += 1;

	for (size_t index = 0; index < m_value.length(); index++)
	{
		char character = m_value[index];

		if (character == '\n')
		{
			screen.x = 0;
			screen.y -= 1;
			continue;
		}

		int start_x = m_position.x + (screen.x * m_size);
		int start_y = m_position.y + (screen.y * m_size);

		Vector<2, float> vertex_up_left(start_x, start_y + m_size);
		Vector<2, float> vertex_up_right(start_x + m_size, start_y + m_size);
		Vector<2, float> vertex_down_right(start_x + m_size, start_y);
		Vector<2, float> vertex_down_left(start_x, start_y);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		float uv_x = ((character % 16) / 16.0f);
		float uv_y = ((character / 16) / 16.0f);

		Vector<2, float> uv_up_left(uv_x, -uv_y);
		Vector<2, float> uv_up_right((uv_x + 1.0f / 16.0f), -uv_y);
		Vector<2, float> uv_down_right((uv_x + 1.0f / 16.0f), -(uv_y + 1.0f / 16.0f));
		Vector<2, float> uv_down_left(uv_x, -(uv_y + 1.0f / 16.0f));

		uvs.push_back(uv_up_left);
		uvs.push_back(uv_down_left);
		uvs.push_back(uv_up_right);

		uvs.push_back(uv_down_right);
		uvs.push_back(uv_up_right);
		uvs.push_back(uv_down_left);

		screen.x += 1;
	}

	m_vertex_buffer.store(vertices);
	m_uv_buffer.store(uvs);

	m_invalidated = false;
}

void
TextMesh::set(const std::string &value)
{
	if (m_value == value)
		return;

	m_value = value;
	invalidate();
}
void
TextMesh::set_and_build(const std::string &value)
{
	set(value);

	if (is_invalidated())
		build();
}
