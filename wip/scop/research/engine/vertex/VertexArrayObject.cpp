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

VertexArrayObject::VertexArrayObject() :
		m_id(-1),
		m_attached()
{
	glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_id);

	typedef typename std::vector<std::pair<VertexBufferObject*, bool>>::const_iterator const_iterator;
	for (const_iterator iterator = m_attached.begin(); iterator != m_attached.end(); ++iterator)
		if (iterator->second)
			delete iterator->first;
}

bool
VertexArrayObject::add(VertexBufferObject &object, bool auto_delete)
{
	/* vector lookup is bad :/ */
	typedef typename std::vector<std::pair<VertexBufferObject*, bool>>::const_iterator const_iterator;
	for (const_iterator iterator = m_attached.begin(); iterator != m_attached.end(); ++iterator)
		if (iterator->first == &object)
			return (false);

	bind();
	object.bind();

	m_attached.push_back(std::make_pair(&object, auto_delete));

	return (true);
}

VertexBufferObject&
VertexArrayObject::get(size_t index)
{
	return (*m_attached.at(index).first);
}

void
VertexArrayObject::bind()
{
	glBindVertexArray(m_id);
}

void
VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}
