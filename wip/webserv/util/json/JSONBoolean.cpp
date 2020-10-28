/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONBoolean.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:38:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:38:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONBoolean.hpp>

JSONBoolean::JSONBoolean(void) :
		m_value(false)
{
}

JSONBoolean::JSONBoolean(bool value) :
		m_value(value)
{
}

JSONBoolean::JSONBoolean(const JSONBoolean &other) :
		m_value(other.m_value)
{
}

JSONBoolean::~JSONBoolean(void)
{
}

JSONBoolean&
JSONBoolean::operator =(const JSONBoolean &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JSONBoolean&
JSONBoolean::operator =(const bool &value)
{
	m_value = value;

	return (*this);
}

std::string
JSONBoolean::toJsonString() const
{
	return (m_value ? "true" : "false");
}

JSONBase*
JSONBoolean::clone() const
{
	return (new JSONBoolean(*this));
}

JSONBoolean::operator bool(void)
{
	return (m_value);
}

JSONBoolean::operator bool(void) const
{
	return (m_value);
}
