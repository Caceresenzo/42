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

TextMesh::TextMesh(SharedReference<Font> &font, const std::string &initial, const Vector<2, float> &position, float size) :
	font(font),
	value(initial),
	position(position),
	size(size),
	vertex_array(*new VertexArrayObject()),
	vertex_buffer(*new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::DYNAMIC_DRAW)),
	uv_buffer(*new VertexBufferObject(VertexBufferObject::ARRAY, VertexBufferObject::DYNAMIC_DRAW))
{
	vertex_array->add(vertex_buffer);
	vertex_array->add(uv_buffer);
}

TextMesh::~TextMesh()
{
}

void
TextMesh::build()
{
	std::vector<Vector<2, float> > vertices;
	std::vector<Vector<2, float> > uvs;

	size_t estimated = value.length() * (3 + 3);
	vertices.reserve(estimated);
	uvs.reserve(estimated);

	Vector<2, int> screen(0, 0);

	for (size_t index = 0; index < value.length(); index++)
		if (value[index] == '\n')
			screen.y += 1;

	for (size_t index = 0; index < value.length(); index++)
	{
		char character = value[index];

		if (character == '\n')
		{
			screen.x = 0;
			screen.y -= 1;
			continue;
		}

		if (character == ' ')
		{
			screen.x += 1;
			continue;
		}

		int start_x = position.x + (screen.x * size * font->character_dimension.x);
		int start_y = position.y + (screen.y * size * font->character_dimension.y);

		Vector<2, float> vertex_up_left(start_x, start_y + size);
		Vector<2, float> vertex_up_right(start_x + size, start_y + size);
		Vector<2, float> vertex_down_right(start_x + size, start_y);
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

	vertex_buffer->store(vertices);
	uv_buffer->store(uvs);
}

void
TextMesh::set(const std::string &value)
{
	this->value = value;
	build();
}
