/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONException.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:05:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/23 17:05:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONException.hpp>

JSONException::JSONException(void) :
		m_source(""),
		m_index(-1)
{
}

JSONException::JSONException(const std::string &message, const std::string &source, std::size_t index) :
		Exception(message),
		m_source(source),
		m_index(index)
{
}

JSONException::JSONException(const JSONException &other) :
		m_source(other.m_source),
		m_index(other.m_index)
{
}

JSONException::~JSONException() throw ()
{
}

JSONException&
JSONException::operator =(const JSONException &other)
{
	Exception::operator =(other);

	if (this != &other)
	{
		m_source = other.m_source;
		m_index = other.m_index;
	}

	return (*this);
}

const std::string&
JSONException::source() const
{
	return (m_source);
}

std::size_t
JSONException::index() const
{
	return (m_index);
}
