/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Option.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:29:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 19:29:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lang/IllegalArgumentException.hpp>
#include <util/option/Option.hpp>

Option::Option(char short_name, const std::string &long_name, const std::string &description) :
		m_short(short_name),
		m_long(long_name),
		m_description(description),
		m_argument_name()
{
}

Option::Option(char short_name, const std::string &long_name, const std::string &description, const std::string &argument_name) :
		m_short(short_name),
		m_long(long_name),
		m_description(description),
		m_argument_name(argument_name)
{
	if (m_argument_name.empty())
		throw IllegalArgumentException("argument name must not be empty");
}

Option::~Option(void)
{
}

char
Option::short_name(void) const
{
	return (m_short);
}

const std::string&
Option::long_name(void) const
{
	return (m_long);
}

const std::string&
Option::description(void) const
{
	return (m_description);
}

bool
Option::has_argument(void) const
{
	return (!m_argument_name.empty());
}

const std::string&
Option::argument_name(void) const
{
	return (m_argument_name);
}
