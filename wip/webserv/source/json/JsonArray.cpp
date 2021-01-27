/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonArray.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:55:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:55:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonArray.hpp>
#include <json/JsonValue.hpp>
#include <iterator>

JsonArray::JsonArray(void) :
		m_value()
{
}

JsonArray::JsonArray(std::vector<JsonValue*> value) :
		m_value(value)
{
}

JsonArray::JsonArray(const JsonArray &other) :
		m_value()
{
	operator =(other);
}

JsonArray::~JsonArray(void)
{
	clear();
}

JsonArray&
JsonArray::operator =(const JsonArray &other)
{
	if (this != &other)
	{
		const_iterator it = other.m_value.begin();
		const_iterator ite = other.m_value.end();

		clear();

		for (; it != ite; it++)
			m_value.insert(m_value.end(), (*it)->clone());
	}

	return (*this);
}

JsonValue&
JsonArray::operator [](int index)
{
	return (*(m_value[index]));
}

const JsonValue&
JsonArray::operator [](int index) const
{
	return (*(m_value[index]));
}

JsonArray::operator JsonArray::Container(void)
{
	return (m_value);
}

JsonArray::operator JsonArray::Container(void) const
{
	return (m_value);
}

void
JsonArray::add(JsonValue *value)
{
	m_value.push_back(value);
}

JsonArray::iterator
JsonArray::begin()
{
	return (m_value.begin());
}

JsonArray::iterator
JsonArray::end()
{
	return (m_value.end());
}

JsonArray::const_iterator
JsonArray::begin() const
{
	return (m_value.begin());
}

JsonArray::const_iterator
JsonArray::end() const
{
	return (m_value.end());
}

void
JsonArray::clear(void)
{
	if (m_value.empty())
		return;

	for (iterator it = m_value.begin(); it != m_value.end(); it++)
		delete *it;

	return (m_value.clear());
}

bool
JsonArray::empty() const
{
	return (m_value.empty());
}

JsonArray::Container::size_type
JsonArray::size() const
{
	return (m_value.size());
}

JsonValue*
JsonArray::clone(void) const
{
	return (new JsonArray(*this));
}

JsonArray::Type
JsonArray::type(void) const
{
	return (TYPE_ARRAY);
}

const std::string
JsonArray::toJsonString(void) const
{
	std::string out("[");

	for (const_iterator it = m_value.begin(); it != m_value.end(); it++)
	{
		out += (*it)->toJsonString();

		if (++it != m_value.end())
			out += ',';
	}

	out += ']';

	return (out);
}

bool
JsonArray::equals(const JsonValue &other) const
{
	const JsonArray *casted = dynamic_cast<JsonArray const*>(&other);
	if (casted)
	{
		size_type size = this->size();
		if (size != casted->size())
			return (false);

		for (size_type index = 0; index < size; index++)
		{
			if (this->operator [](index) != casted->operator [](index))
				return (false);
		}

		return (true);
	}

	return (false);
}
