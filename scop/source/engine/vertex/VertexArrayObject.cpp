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
	m_id(-1)
{
//	std::cout << "VertexArrayObject glGenVertexArrays(1, ...): ";
	glGenVertexArrays(1, &m_id);
	OpenGL::check_error();
//	std::cout << m_id << std::endl;
}

VertexArrayObject::~VertexArrayObject()
{
//	std::cout << "VertexArrayObject glDeleteVertexArrays(1, id=" << m_id << "): ";
	glDeleteVertexArrays(1, &m_id);
	OpenGL::check_error();
//	std::cout << "void" << std::endl;
}

void
VertexArrayObject::bind()
{
//	std::cout << "VertexArrayObject glBindVertexArray(id=" << m_id << "): ";
	glBindVertexArray(m_id);
	OpenGL::check_error();
//	std::cout << "void" << std::endl;
}

void
VertexArrayObject::unbind()
{
//	std::cout << "VertexArrayObject glBindVertexArray(id=" << 0 << "): ";
	glBindVertexArray(0);
	OpenGL::check_error();
//	std::cout << "void" << std::endl;
}

void
VertexArrayObject::add(SharedReference<VertexBufferObject> &object)
{
	bind();
	object->bind();
}
