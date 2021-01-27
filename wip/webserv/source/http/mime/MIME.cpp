/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mime.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:37:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/26 17:37:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/mime/MIME.hpp>
#include <util/helper/JsonBinderHelper.hpp>
#include <json/JsonString.hpp>

MIME::MIME(void) :
		m_type(),
		m_extensions()
{
}

MIME::MIME(const string &type, const string &extension) :
		m_type(type),
		m_extensions()
{
	m_extensions.push_back(extension);
}

MIME::MIME(const string &type, const list &extensions) :
		m_type(type),
		m_extensions(extensions)
{
}

MIME::MIME(const MIME &other) :
		m_type(other.m_type),
		m_extensions(other.m_extensions)
{
}

MIME&
MIME::operator =(const MIME &other)
{
	if (this != &other)
	{
		m_type = other.m_type;
		m_extensions = other.m_extensions;
	}

	return (*this);
}

const MIME::string&
MIME::type(void) const
{
	return (m_type);
}

const MIME::list&
MIME::extensions(void) const
{
	return (m_extensions);
}

MIME*
MIME::builder(const std::string &path, const std::string &key, const JsonArray &jsonArray)
{
	const std::string &type = key;
	const std::list<std::string> extensions = JsonBinderHelper::buildCollection<JsonString, std::string>(path, jsonArray);

	return (new MIME(type, extensions));
}

std::list<MIME const*>
MIME::builder(const std::string &path, const JsonObject &jsonObject)
{
	return (JsonBinderHelper::buildBlocks<MIME, JsonArray>(path, jsonObject, MIME::builder));
}
