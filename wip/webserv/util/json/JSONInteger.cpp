/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONInteger.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:42:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:42:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONInteger.hpp>
#include <sstream>

JSONInteger::JSONInteger(void) :
		m_value(0)
{
}

JSONInteger::JSONInteger(long value) :
		m_value(value)
{
}

JSONInteger::JSONInteger(const JSONInteger &other) :
		m_value(other.m_value)
{
}

JSONInteger::~JSONInteger(void)
{
}

JSONInteger&
JSONInteger::operator =(const JSONInteger &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JSONInteger&
JSONInteger::operator =(const long &value)
{
	m_value = value;

	return (*this);
}

std::string
JSONInteger::toJsonString() const
{
	std::stringstream stream;
	stream << m_value;

	return (stream.str());
}

JSONBase*
JSONInteger::clone() const
{
	return (new JSONInteger(*this));
}

JSONInteger::operator long(void)
{
	return (m_value);
}

JSONInteger::operator long(void) const
{
	return (m_value);
}

long
JSONInteger::value(void)
{
	return (m_value);
}
