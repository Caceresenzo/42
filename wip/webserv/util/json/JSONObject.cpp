/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONObject.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:18:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 18:18:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONObject.hpp>

JSONObject::JSONObject(void) :
		m_map()
{
}

JSONObject::JSONObject(container map) :
		m_map(map)
{
}

JSONObject::JSONObject(const JSONObject &other) :
		m_map(other.m_map)
{
}

JSONObject::~JSONObject()
{
}

JSONObject&
JSONObject::operator =(const JSONObject &other)
{
	if (this != &other)
		m_map = other.m_map;

	return (*this);
}

std::string
JSONObject::toJsonString() const
{
	return ("");
}

JSONBase*
JSONObject::clone() const
{
	return (new JSONObject(*this));
}

JSONObject::size_type
JSONObject::size(void)
{
	return (m_map.size());
}

void
JSONObject::put(const std::string &key, JSONType value)
{
	m_map[key] = value;
}

bool
JSONObject::has(const std::string &key) const
{
	return (find(key) != end());
}

JSONType&
JSONObject::get(const std::string &key)
{
	return (find(key)->second);
}

JSONObject::iterator
JSONObject::find(const std::string &key)
{
	return (m_map.find(key));
}

JSONObject::const_iterator
JSONObject::find(const std::string &key) const
{
	return (m_map.find(key));
}

JSONObject::iterator
JSONObject::begin(void)
{
	return (m_map.begin());
}

JSONObject::const_iterator
JSONObject::begin(void) const
{
	return (m_map.begin());
}

JSONObject::iterator
JSONObject::end(void)
{
	return (m_map.end());
}

JSONObject::const_iterator
JSONObject::end(void) const
{
	return (m_map.end());
}

JSONObject::container&
JSONObject::value(void)
{
	return (m_map);
}
