/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArrayObject.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:31:58 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 23:31:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/vertex/VertexArrayObject.hpp>
#include <lang/reference/SharedReference.hpp>

VertexArrayObject::VertexArrayObject() :
	m_id(-1),
	m_attached()
{
	glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_id);
}

bool
VertexArrayObject::add(SharedReference<VertexBufferObject> &object)
{
	/* vector lookup is bad :/ */
	for (iterator iterator = m_attached.begin(); iterator != m_attached.end(); ++iterator)
		if (iterator->value() == object.value())
			return (false);

	bind();
	object->bind();

	m_attached.push_back(object);

	return (true);
}

SharedReference<VertexBufferObject>
VertexArrayObject::get(size_t index)
{
	return (m_attached.at(index));
}

void
VertexArrayObject::bind(bool with_attached)
{
	glBindVertexArray(m_id);

	if (with_attached)
		for (iterator iterator = m_attached.begin(); iterator != m_attached.end(); ++iterator)
			(*iterator)->bind();
}

void
VertexArrayObject::unbind(bool with_attached)
{
	glBindVertexArray(0);

	if (with_attached)
		for (iterator iterator = m_attached.begin(); iterator != m_attached.end(); ++iterator)
			(*iterator)->unbind();
}
