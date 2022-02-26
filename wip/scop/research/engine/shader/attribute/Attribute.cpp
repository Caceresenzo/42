/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Attribute.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:28:28 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 21:28:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/attribute/Attribute.hpp>

Attribute::Attribute(const std::string &name, GLint size, GLenum data_type, GLenum normalized) :
		ShaderVariable(name),
		m_size(size),
		m_data_type(data_type),
		m_normalized(normalized)
{
}

Attribute::~Attribute()
{
}

void
Attribute::enable()
{
	glEnableVertexAttribArray(location());
}

void
Attribute::disable()
{
	glDisableVertexAttribArray(location());
}

void
Attribute::link(GLsizei stride, const void *pointer)
{
	glVertexAttribPointer(location(), m_size, m_data_type, m_normalized, stride, pointer);
}

GLint
Attribute::find_location(GLuint program_id, const char *name) const
{
	return (glGetAttribLocation(program_id, name));
}
