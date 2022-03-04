/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBufferObject.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:51:05 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:51:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/vertex/VertexBufferObject.hpp>

VertexBufferObject::VertexBufferObject(BufferType type, UsageType usage) :
		m_id(-1),
		m_type(type),
		m_usage(usage)
{
	glGenBuffers(1, &m_id);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &m_id);
}

void
VertexBufferObject::bind()
{
	glBindBuffer(m_type, m_id);
}

void
VertexBufferObject::unbind()
{
	glBindBuffer(m_type, 0);
}

void
VertexBufferObject::store(GLsizeiptr size, const void *data, bool and_unbind)
{
	bind();
	glBufferData(m_type, size, data, m_usage);

	if (and_unbind)
		unbind();
}
