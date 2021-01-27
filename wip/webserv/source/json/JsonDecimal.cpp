/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonDecimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 19:42:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/02 19:42:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonDecimal.hpp>
#include <iomanip>
#include <sstream>

JsonDecimal::JsonDecimal() :
		m_value(0.0),
		m_precision(1)
{
}

JsonDecimal::JsonDecimal(double value) :
		m_value(value),
		m_precision(1)
{
}
JsonDecimal::JsonDecimal(double value, int precision) :
		m_value(value),
		m_precision(precision)
{
}

JsonDecimal::JsonDecimal(const JsonDecimal &other) :
		m_value(other.m_value),
		m_precision(other.m_precision)
{
}

JsonDecimal::~JsonDecimal()
{
}

JsonDecimal&
JsonDecimal::operator =(const JsonDecimal &other)
{
	if (this != &other)
	{
		m_value = other.m_value;
		m_precision = other.m_precision;
	}

	return (*this);
}

JsonDecimal::operator float()
{
	return (m_value);
}

JsonDecimal::operator float() const
{
	return (m_value);
}

JsonDecimal::operator double()
{
	return (m_value);
}

JsonDecimal::operator double() const
{
	return (m_value);
}

JsonValue*
JsonDecimal::clone() const
{
	return (new JsonDecimal(*this));
}

JsonDecimal::Type
JsonDecimal::type() const
{
	return (TYPE_DECIMAL);
}

const std::string
JsonDecimal::toJsonString() const
{
	std::stringstream sstream;
	sstream << std::fixed << std::setprecision(m_precision) << m_value;

	return (sstream.str());
}

bool
JsonDecimal::equals(const JsonValue &other) const
{
	const JsonDecimal *casted = dynamic_cast<JsonDecimal const*>(&other);
	if (casted)
		return (m_value == casted->m_value);

	return (false);
}
