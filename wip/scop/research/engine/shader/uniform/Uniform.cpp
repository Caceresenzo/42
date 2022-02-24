/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uniform.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 21:28:28 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 21:28:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/exception/RuntimeException.hpp>
#include <engine/shader/ShaderProgram.hpp>
#include <engine/shader/uniform/Uniform.hpp>

Uniform::Uniform(const std::string &name) :
		m_name(name),
		m_location(-1)
{
}

Uniform::Uniform(const Uniform &other) :
		m_name(other.m_name),
		m_location(other.m_location)
{
}

Uniform::~Uniform()
{
}

Uniform&
Uniform::operator =(const Uniform &other)
{
	if (this != &other)
	{
		m_name = other.m_name;
	}

	return (*this);
}

const std::string&
Uniform::name() const
{
	return (m_name);
}

GLint
Uniform::location() const
{
	return (m_location);
}

void
Uniform::locate(const ShaderProgram &program)
{
	GLint location = glGetUniformLocation(program.id(), m_name.c_str());
	if (location == -1)
		throw RuntimeException(m_name + " not found");

	this->m_location = location;
}
