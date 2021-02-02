/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonNumber.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 20:37:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/28 20:37:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonNumber.hpp>

JsonNumber::JsonNumber() :
		m_value(0)
{
}

JsonNumber::JsonNumber(long value) :
		m_value(value)
{
}

JsonNumber::JsonNumber(const JsonNumber &other) :
		m_value(other.m_value)
{
}

JsonNumber::~JsonNumber()
{
}

JsonNumber&
JsonNumber::operator =(const JsonNumber &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JsonNumber::operator int()
{
	return (m_value);
}

JsonNumber::operator int() const
{
	return (m_value);
}

JsonNumber::operator long()
{
	return (m_value);
}

JsonNumber::operator long() const
{
	return (m_value);
}

JsonValue*
JsonNumber::clone() const
{
	return (new JsonNumber(*this));
}

JsonNumber::Type
JsonNumber::type() const
{
	return (TYPE_NUMBER);
}

const std::string
JsonNumber::toJsonString() const
{
	std::stringstream sstream;
	sstream << m_value;

	return (sstream.str());
}

bool
JsonNumber::equals(const JsonValue &other) const
{
	const JsonNumber *casted = dynamic_cast<JsonNumber const*>(&other);
	if (casted)
		return (m_value == casted->m_value);

	return (false);
}
