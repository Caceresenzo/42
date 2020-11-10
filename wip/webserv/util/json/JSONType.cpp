/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONType.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:09:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 18:09:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONType.hpp>

JSONType::JSONType() :
		m_ptr(NULL)
{
}

JSONType::JSONType(bool value) :
		m_ptr(new JSONBoolean(value))
{
}

JSONType::JSONType(int value) :
		m_ptr(new JSONInteger(value))
{
}

JSONType::JSONType(long value) :
		m_ptr(new JSONInteger(value))
{
}

JSONType::JSONType(float value) :
		m_ptr(new JSONDouble(value))
{
}

JSONType::JSONType(double value) :
		m_ptr(new JSONDouble(value))
{
}

JSONType::JSONType(const char *value) :
		m_ptr((value ? (JSONBase*)new JSONString(std::string(value)) : (JSONBase*)new JSONNull()))
{
}

JSONType::JSONType(const std::string &value) :
		m_ptr(new JSONString(value))
{
}

JSONType::JSONType(const JSONNull &jsonNull) :
		m_ptr(new JSONNull(jsonNull))
{
}

JSONType::JSONType(const JSONBoolean &jsonBoolean) :
		m_ptr(new JSONBoolean(jsonBoolean))
{
}

JSONType::JSONType(const JSONInteger &jsonInteger) :
		m_ptr(new JSONInteger(jsonInteger))
{
}

JSONType::JSONType(const JSONDouble &jsonDouble) :
		m_ptr(new JSONDouble(jsonDouble))
{
}

JSONType::JSONType(const JSONString &jsonString) :
		m_ptr(new JSONString(jsonString))
{
}

JSONType::JSONType(const JSONArray &jsonArray) :
		m_ptr(new JSONArray(jsonArray))
{
}

JSONType::JSONType(const JSONObject &jsonObject) :
		m_ptr(new JSONObject(jsonObject))
{
}

JSONType::JSONType(const JSONType &other) :
		m_ptr(NULL)
{
	operator =(other);
}

JSONType::~JSONType()
{
	if (m_ptr)
	{
		delete m_ptr;
		m_ptr = NULL;
	}
}

JSONType&
JSONType::operator =(const JSONType &other)
{
	if (this != &other)
	{
		if (m_ptr)
		{
			delete m_ptr;
			m_ptr = NULL;
		}

		if (other.m_ptr)
			m_ptr = other.m_ptr->clone();
	}

	return (*this);
}

std::string
JSONType::toJsonString() const
{
	return (m_ptr->toJsonString());
}

JSONType::operator JSONNull(void) const
{
	return (*static_cast<JSONNull*>(this->m_ptr));
}

JSONType::operator JSONNull&(void)
{
	return (*static_cast<JSONNull*>(this->m_ptr));
}

JSONType::operator bool(void) const
{
	return (*static_cast<JSONBoolean*>(this->m_ptr));
}

JSONType::operator bool(void)
{
	return (*static_cast<JSONBoolean*>(this->m_ptr));
}

JSONType::operator JSONBoolean(void) const
{
	return (*static_cast<JSONBoolean*>(this->m_ptr));
}

JSONType::operator JSONBoolean&(void)
{
	return (*static_cast<JSONBoolean*>(this->m_ptr));
}

JSONType::operator int(void) const
{
	return (*static_cast<JSONInteger*>(this->m_ptr));
}

JSONType::operator int(void)
{
	return (*static_cast<JSONInteger*>(this->m_ptr));
}

JSONType::operator long(void) const
{
	return (*static_cast<JSONInteger*>(this->m_ptr));
}

JSONType::operator long(void)
{
	return (*static_cast<JSONInteger*>(this->m_ptr));
}

JSONType::operator JSONInteger(void) const
{
	return (*static_cast<JSONInteger*>(this->m_ptr));
}

JSONType::operator JSONInteger&(void)
{
	return (*static_cast<JSONInteger*>(this->m_ptr));
}

JSONType::operator float(void) const
{
	return (*static_cast<JSONDouble*>(this->m_ptr));
}

JSONType::operator float(void)
{
	return (*static_cast<JSONDouble*>(this->m_ptr));
}

JSONType::operator double(void) const
{
	return (*static_cast<JSONDouble*>(this->m_ptr));
}

JSONType::operator double(void)
{
	return (*static_cast<JSONDouble*>(this->m_ptr));
}

JSONType::operator JSONDouble(void) const
{
	return (*static_cast<JSONDouble*>(this->m_ptr));
}

JSONType::operator JSONDouble&(void)
{
	return (*static_cast<JSONDouble*>(this->m_ptr));
}

JSONType::operator std::string(void) const
{
	return (static_cast<JSONString*>(this->m_ptr)->value());
}

JSONType::operator std::string&(void)
{
	return (static_cast<JSONString*>(this->m_ptr)->value());
}

JSONType::operator JSONString(void) const
{
	return (*static_cast<JSONString*>(this->m_ptr));
}

JSONType::operator JSONString&(void)
{
	return (*static_cast<JSONString*>(this->m_ptr));
}

JSONType::operator JSONArray(void) const
{
	return (*static_cast<JSONArray*>(this->m_ptr));
}

JSONType::operator JSONArray&(void)
{
	return (*static_cast<JSONArray*>(this->m_ptr));
}

JSONType::operator JSONObject(void) const
{
	return (*static_cast<JSONObject*>(this->m_ptr));
}

JSONType::operator JSONObject&(void)
{
	return (*static_cast<JSONObject*>(this->m_ptr));
}
