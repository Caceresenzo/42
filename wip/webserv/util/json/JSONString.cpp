/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONString.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:42:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:42:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONString.hpp>

JSONString::JSONString(void) :
		m_value(0)
{
}

JSONString::JSONString(std::string value) :
		m_value(value)
{
}

JSONString::JSONString(const JSONString &other) :
		m_value(other.m_value)
{
}

JSONString::~JSONString()
{
}

JSONString&
JSONString::operator =(const JSONString &other)
{
	if (this != &other)
		m_value = other.m_value;

	return (*this);
}

JSONString&
JSONString::operator =(const std::string &value)
{
	m_value = value;

	return (*this);
}

std::string
JSONString::toJsonString() const
{
	return (m_value); // TODO Escape
}

JSONBase*
JSONString::clone() const
{
	return (new JSONString(*this));
}

JSONString::operator std::string(void)
{
	return (m_value);
}

JSONString::operator std::string(void) const
{
	return (m_value);
}

std::string&
JSONString::value(void)
{
	return (m_value);
}

std::string
JSONString::value(void) const
{
	return (m_value);
}
