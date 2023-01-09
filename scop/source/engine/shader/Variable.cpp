/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderVariable.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:25:42 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/26 21:25:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/Program.hpp>
#include <engine/shader/Variable.hpp>
#include <lang/RuntimeException.hpp>

Variable::Variable(const std::string &name) :
		m_name(name),
		m_location(-1)
{
}

Variable::~Variable()
{
}

void
Variable::locate(const Program &program)
{
	GLint location = find_location(program.id(), m_name.c_str());
	if (location == -1)
		throw RuntimeException(m_name + " not found");

	this->m_location = location;
}
