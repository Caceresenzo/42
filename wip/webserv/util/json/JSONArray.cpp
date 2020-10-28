/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONArray.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:08:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 18:08:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONArray.hpp>

JSONArray::JSONArray(void) :
		m_array()
{
}

JSONArray::JSONArray(container array) :
		m_array(array)
{
}

JSONArray::JSONArray(const JSONArray &other) :
		m_array(other.m_array)
{
}

JSONArray::~JSONArray(void)
{
}

JSONArray&
JSONArray::operator =(const JSONArray &other)
{
	if (this != &other)
		m_array = other.m_array;

	return (*this);
}

JSONType&
JSONArray::operator [](int n)
{
	return (m_array[n]);
}

std::string
JSONArray::toJsonString() const
{
	return ("");
}

JSONBase*
JSONArray::clone() const
{
	return (new JSONArray(*this));
}

bool
JSONArray::empty(void)
{
	return (m_array.empty());
}

JSONArray::size_type
JSONArray::size(void)
{
	return (m_array.size());
}

void
JSONArray::add(const JSONType &jsonType)
{
	m_array.push_back(jsonType);
}

JSONType&
JSONArray::get(size_type index)
{
	return (m_array.at(index));
}

JSONArray::iterator
JSONArray::begin(void)
{
	return (m_array.begin());
}

JSONArray::const_iterator
JSONArray::begin(void) const
{
	return (m_array.begin());
}

JSONArray::iterator
JSONArray::end(void)
{
	return (m_array.end());
}

JSONArray::const_iterator
JSONArray::end(void) const
{
	return (m_array.end());
}
