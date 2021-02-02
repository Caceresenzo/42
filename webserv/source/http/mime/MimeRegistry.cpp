/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeRegistry.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:39:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/24 16:22:30 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/mime/MIME.hpp>
#include <http/mime/MIMERegistry.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonReader.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>

Logger &MIMERegistry::LOG = LoggerFactory::get("MIME Registry");

MIMERegistry::MIMERegistry(void) :
		m_mapping(),
		m_reverse_mapping()
{
}

MIMERegistry::MIMERegistry(const map &mapping, const map &reverse_mapping) :
		m_mapping(mapping),
		m_reverse_mapping(reverse_mapping)
{
}

MIMERegistry::MIMERegistry(const MIMERegistry &other) :
		m_mapping(other.m_mapping),
		m_reverse_mapping(other.m_reverse_mapping)
{
}

MIMERegistry::~MIMERegistry(void)
{
	clear();
}

MIMERegistry&
MIMERegistry::operator =(const MIMERegistry &other)
{
	if (this != &other)
	{
		copyMapping(other.m_mapping, m_mapping);
		copyMapping(other.m_reverse_mapping, m_reverse_mapping);
	}

	return (*this);
}

void
MIMERegistry::copyMapping(const map &from, map &to)
{
	clearMapping(to);

	for (const_iterator it = from.begin(); it != from.end(); it++)
		to.insert(to.end(), std::make_pair(it->first, new MIME(*(it->second))));
}

void
MIMERegistry::clearMapping(map &mapping)
{
	if (mapping.empty())
		return;

	for (const_iterator it = mapping.begin(); it != mapping.end(); it++)
		delete it->second;

	mapping.clear();
}

void
MIMERegistry::add(const MIME &mime)
{
	const MIME *old;

	if ((old = findByMimeType(mime.type())) != NULL)
		delete old;

	m_mapping[mime.type()] = new MIME(mime);

	MIME::iterator it = mime.extensions().begin();
	MIME::iterator ite = mime.extensions().end();
	while (it != ite)
	{
		const std::string &extension = *it;

		if ((old = findByFileExtension(extension)) != NULL) // TODO Make merging instead of replace
			delete old;

		m_reverse_mapping[extension] = new MIME(mime);

		it++;
	}
}

void
MIMERegistry::clear(void)
{
	clearMapping(m_mapping);
	clearMapping(m_reverse_mapping);
}

const MIME*
MIMERegistry::MIMERegistry::findByMimeType(const std::string &type) const
{
	const_iterator it = m_mapping.find(type);
	if (it == m_mapping.end())
		return (NULL);

	return (it->second);
}

const MIME*
MIMERegistry::findByFileExtension(const std::string &extension) const
{
	const_iterator it = m_reverse_mapping.find(extension);

	if (it == m_reverse_mapping.end())
		return (NULL);

	return (it->second);
}

void
MIMERegistry::loadFromFile(const std::string &path)
{
	JsonObject *object = JsonReader::fromFile(path).readObject();

	try
	{
		loadFromJson("<root: " + path + ">", *object);

		LOG.debug() << "Loaded " << size() << " MIME(s)" << std::endl;

		delete object;
	}
	catch (...)
	{
		delete object;
		throw;
	}
}

void
MIMERegistry::loadFromJson(const std::string &path, const JsonObject &jsonObject)
{
	std::list<MIME const*> mimes = MIME::builder(path, jsonObject);

	for (std::list<MIME const*>::iterator it = mimes.begin(); it != mimes.end(); it++)
		add(*(*it));

	DeleteHelper::pointers(mimes);
}

size_t
MIMERegistry::size() const
{
	return (m_mapping.size());
}
