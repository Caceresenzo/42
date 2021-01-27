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

#include <exception/IllegalArgumentException.hpp>
#include <options/Option.hpp>

Option::Option(char shortName, std::string longName, std::string description) :
		m_short(shortName),
		m_long(longName),
		m_description(description),
		m_argumentName()
{
}

Option::Option(char shortName, std::string longName, std::string description, std::string argumentName) :
		m_short(shortName),
		m_long(longName),
		m_description(description),
		m_argumentName(argumentName)
{
	if (m_argumentName.empty())
		throw IllegalArgumentException("argument name must not be empty");
}

Option::~Option(void)
{
}

char
Option::shortName(void) const
{
	return (m_short);
}

const std::string&
Option::longName(void) const
{
	return (m_long);
}

const std::string&
Option::description(void) const
{
	return (m_description);
}

bool
Option::hasArgument(void) const
{
	return (!m_argumentName.empty());
}

const std::string&
Option::argumentName(void) const
{
	return (m_argumentName);
}
