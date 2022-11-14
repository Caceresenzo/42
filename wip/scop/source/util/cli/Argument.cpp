/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Argument.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:56:42 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/14 00:56:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/cli/Argument.hpp>

Argument::Argument(std::string name, bool optional) :
	m_name(name),
	m_optional(optional)
{
}

Argument::Argument(std::string name, bool optional, std::string description) :
	m_name(name),
	m_optional(optional),
	m_description(description)
{
}

Argument::~Argument()
{
}

std::string
Argument::format_name() const
{
	if (m_optional)
		return ("[" + m_name + "]");
	else
		return ("<" + m_name + ">");
}
