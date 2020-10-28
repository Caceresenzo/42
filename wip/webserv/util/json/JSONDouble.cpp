/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONDouble.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:42:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:42:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONDouble.hpp>
#include <sstream>

JSONDouble::JSONDouble(void) :
		m_value(0)
{
}

JSONDouble::JSONDouble(double value) :
		m_value(value)
{
}

JSONDouble::JSONDouble(const JSONDouble &other) :
		m_value(other.m_value)
{
}

JSONDouble::~JSONDouble(void)
{
}

JSONDouble&
JSONDouble::operator =(const JSONDouble &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JSONDouble&
JSONDouble::operator =(const double &value)
{
	m_value = value;

	return (*this);
}

std::string
JSONDouble::toJsonString() const
{
	std::stringstream stream;
	stream << m_value;

	return (stream.str());
}

JSONBase*
JSONDouble::clone() const
{
	return (new JSONDouble(*this));
}

JSONDouble::operator double(void)
{
	return (m_value);
}

JSONDouble::operator double(void) const
{
	return (m_value);
}

double
JSONDouble::value(void)
{
	return (m_value);
}
