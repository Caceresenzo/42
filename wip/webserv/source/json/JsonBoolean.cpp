/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonBoolean.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:48:59 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 18:48:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonBoolean.hpp"

const std::string JsonBoolean::TRUE = "true";
const std::string JsonBoolean::FALSE = "false";

JsonBoolean::JsonBoolean() :
		m_value(false)
{
}

JsonBoolean::JsonBoolean(bool value) :
		m_value(value)
{
}

JsonBoolean::JsonBoolean(const JsonBoolean &other) :
		m_value(other.m_value)
{
}

JsonBoolean::~JsonBoolean()
{
}

JsonBoolean&
JsonBoolean::operator =(const JsonBoolean &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JsonBoolean::operator bool()
{
	return (m_value);
}

JsonBoolean::operator bool() const
{
	return (m_value);
}

JsonValue*
JsonBoolean::clone() const
{
	return (new JsonBoolean(*this));
}

JsonBoolean::Type
JsonBoolean::type() const
{
	return (TYPE_BOOLEAN);
}

const std::string
JsonBoolean::toJsonString() const
{
	return (m_value ? TRUE : FALSE);
}

bool
JsonBoolean::equals(const JsonValue &other) const
{
	const JsonBoolean *casted = dynamic_cast<JsonBoolean const*>(&other);
	if (casted)
		return (m_value == casted->m_value);

	return (false);
}
