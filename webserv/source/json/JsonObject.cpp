/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonObject.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:31:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/helper/DeleteHelper.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonUtils.hpp>
#include <json/JsonValue.hpp>
#include <utility>

JsonObject::JsonObject(void) :
		m_value()
{
}

JsonObject::JsonObject(Container value) :
		m_value(value)
{
}

JsonObject::JsonObject(const JsonObject &other) :
		m_value()
{
	operator =(other);
}

JsonObject::~JsonObject(void)
{
	clear();
}

JsonObject&
JsonObject::operator =(const JsonObject &other)
{
	if (this != &other)
	{
		clear();

		for (const_iterator it = other.begin(); it != other.end(); it++)
			m_value.insert(m_value.end(), std::make_pair(it->first, it->second->clone()));
	}

	return (*this);
}

JsonObject::operator JsonObject::Container(void)
{
	return (m_value);
}

JsonObject::operator JsonObject::Container(void) const
{
	return (m_value);
}

void
JsonObject::put(const std::string &name, JsonValue *value)
{
	DeleteHelper::pointer<JsonValue>(m_value[name]);

	m_value[name] = value;
}

bool
JsonObject::has(const std::string &name) const
{
	return (m_value.find(name) != m_value.end());
}

JsonValue*
JsonObject::get(const std::string &name)
{
	const_iterator it = m_value.find(name);

	if (it == m_value.end())
		return (NULL);

	return (it->second);
}

const JsonValue*
JsonObject::get(const std::string &name) const
{
	const_iterator it = m_value.find(name);

	if (it == m_value.end())
		return (NULL);

	return (it->second);
}

JsonObject::iterator
JsonObject::begin()
{
	return (m_value.begin());
}

JsonObject::iterator
JsonObject::end()
{
	return (m_value.end());
}

JsonObject::const_iterator
JsonObject::begin() const
{
	return (m_value.begin());
}

JsonObject::const_iterator
JsonObject::end() const
{
	return (m_value.end());
}

JsonObject::iterator
JsonObject::find(const std::string &key)
{
	return (m_value.find(key));
}

JsonObject::const_iterator
JsonObject::find(const std::string &key) const
{
	return (m_value.find(key));
}

void
JsonObject::clear(void)
{
	if (m_value.empty())
		return;

	iterator it = m_value.begin();
	iterator ite = m_value.end();

	for (; it != ite; it++)
		delete it->second;

	return (m_value.clear());
}

bool
JsonObject::empty() const
{
	return (m_value.empty());
}

JsonObject::Container::size_type
JsonObject::size() const
{
	return (m_value.size());
}

JsonValue*
JsonObject::clone(void) const
{
	return (new JsonObject(*this));
}

JsonObject::Type
JsonObject::type(void) const
{
	return (TYPE_OBJECT);
}

const std::string
JsonObject::toJsonString() const
{
	std::string out("{");

	for (const_iterator it = m_value.begin(); it != m_value.end(); it++)
	{
		out += JsonUtils::escapeString(it->first);
		out += ':';
		out += it->second->toJsonString();

		if (++it != m_value.end())
			out += ',';
	}

	out += '}';

	return (out);
}

bool
JsonObject::equals(const JsonValue &other) const
{
	const JsonObject *casted = dynamic_cast<JsonObject const*>(&other);
	if (casted)
	{
		if (size() != casted->size())
			return (false);

		for (const_iterator it = begin(); it != end(); it++)
		{
			const_iterator found = casted->find(it->first);

			if (found == casted->end())
				return (false);

			if (*it->second != *found->second)
				return (false);
		}

		return (true);
	}

	return (false);
}
