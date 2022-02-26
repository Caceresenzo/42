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

#include <engine/math/vector.hpp>
#include <engine/text/Text.hpp>
#include <stddef.h>
#include <cstring>
#include <iostream>
#include <vector>

Text::Text(const std::string &initial, const Vector2f &position, float size) :
		m_value(initial),
		m_position(position),
		m_size(size),
		m_invalidated(true),
		m_vertex_buffer_id(-1),
		m_uv_buffer_id(-1)
{
	glGenBuffers(1, &m_vertex_buffer_id);
	glGenBuffers(1, &m_uv_buffer_id);
}

Text::~Text()
{
	glDeleteBuffers(1, &m_vertex_buffer_id);
	glDeleteBuffers(1, &m_uv_buffer_id);
}

void
Text::invalidate()
{
	m_invalidated = true;
}

bool
Text::is_invalidated() const
{
	return (m_invalidated);
}

const std::string&
Text::get() const
{
	return (m_value);
}

void
Text::build()
{
	std::vector<Vector2<float>> vertices;
	std::vector<Vector2<float>> uvs;

	size_t estimated = m_value.length() * (3 + 3);
	vertices.reserve(estimated);
	uvs.reserve(estimated);

	for (size_t index = 0; index < m_value.length(); index++)
	{
		Vector2<float> vertex_up_left(m_position.x + index * m_size, m_position.y + m_size);
		Vector2<float> vertex_up_right(m_position.x + index * m_size + m_size, m_position.y + m_size);
		Vector2<float> vertex_down_right(m_position.x + index * m_size + m_size, m_position.y);
		Vector2<float> vertex_down_left(m_position.x + index * m_size, m_position.y);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = m_value[index];
		float uv_x = ((character % 16) / 16.0f);
		float uv_y = ((character / 16) / 16.0f);

		Vector2<float> uv_up_left(uv_x, -uv_y);
		Vector2<float> uv_up_right((uv_x + 1.0f / 16.0f), -uv_y);
		Vector2<float> uv_down_right((uv_x + 1.0f / 16.0f), -(uv_y + 1.0f / 16.0f));
		Vector2<float> uv_down_left(uv_x, -(uv_y + 1.0f / 16.0f));

		uvs.push_back(uv_up_left);
		uvs.push_back(uv_down_left);
		uvs.push_back(uv_up_right);

		uvs.push_back(uv_down_right);
		uvs.push_back(uv_up_right);
		uvs.push_back(uv_down_left);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2<float> ), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, m_uv_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2<float> ), &uvs[0], GL_STATIC_DRAW);

	m_invalidated = false;
}

void
Text::set(const std::string &value)
{
	if (m_value == value)
		return;

	m_value = value;
	invalidate();
}
