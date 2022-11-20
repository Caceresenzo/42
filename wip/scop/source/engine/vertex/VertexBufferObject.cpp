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

#include <cxxabi.h>
#include <engine/vertex/VertexBufferObject.hpp>
#include <stddef.h>
#include <iostream>
#include <typeinfo>

VertexBufferObject::VertexBufferObject(BufferType type, UsageType usage) :
	m_id(-1),
	m_type(type),
	m_usage(usage)
{
//	std::cout << "VertexBufferObject glGenBuffers(1, ...): ";
	glGenBuffers(1, &m_id);
	OpenGL::check_error();
//	std::cout << m_id << std::endl;
}

VertexBufferObject::~VertexBufferObject()
{
//	std::cout << "VertexBufferObject glDeleteBuffers(1, id=" << m_id << "): ";
	glDeleteBuffers(1, &m_id);
	OpenGL::check_error();
//	std::cout << "void" << std::endl;
}

void
VertexBufferObject::bind()
{
//	std::cout << "VertexBufferObject glBindBuffer(m_type="<< m_type <<", id=" << m_id << "): ";
	glBindBuffer(m_type, m_id);
	OpenGL::check_error();
//	std::cout << "void" << std::endl;
}

void
VertexBufferObject::unbind()
{
//	std::cout << "VertexBufferObject glBindBuffer(m_type="<< m_type <<", id=" << 0 << "): ";
	glBindBuffer(m_type, 0);
	OpenGL::check_error();
//	std::cout << "void" << std::endl;
}

void
VertexBufferObject::store(GLsizeiptr size, const void *data, bool and_unbind)
{
	bind();

//	std::cout << abi::__cxa_demangle(typeid(*this).name(), NULL, NULL, NULL)
//		<< " glBufferData("
//		<< "m_type=" << m_type
//		<< ", size=" << size
//		<< ", data=" << data
//		<< ", m_usage=" << m_usage
//		<< "): " << std::flush;

	glBufferData(m_type, size, data, m_usage);
	OpenGL::check_error();

//	std::cout << "void" << std::endl;

	if (and_unbind)
		unbind();
}
