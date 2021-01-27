/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonString.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 20:40:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/28 20:40:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonString.hpp>

JsonString::JsonString() :
		m_value()
{
}

JsonString::JsonString(const char *value) :
		m_value(value)
{
}

JsonString::JsonString(const std::string &value) :
		m_value(value)
{
}

JsonString::JsonString(const JsonString &other) :
		m_value(other.m_value)
{
}

JsonString::~JsonString()
{
}

JsonString&
JsonString::operator =(const JsonString &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JsonString::operator std::string()
{
	return (m_value);
}

JsonString::operator std::string() const
{
	return (m_value);
}

JsonValue*
JsonString::clone() const
{
	return (new JsonString(*this));
}

JsonString::Type
JsonString::type() const
{
	return (TYPE_STRING);
}

const std::string
JsonString::toJsonString() const
{
	return (JsonUtils::escapeString(m_value));
}

bool
JsonString::equals(const JsonValue &other) const
{
	const JsonString *casted = dynamic_cast<JsonString const*>(&other);
	if (casted)
		return (m_value == casted->m_value);

	return (false);
}
