/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:51:13 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 18:51:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/RootBlock.hpp>
#include <config/Configuration.hpp>
#include <http/request/HTTPRequest.hpp>
#include <io/File.hpp>
#include <util/Collections.hpp>
#include <util/Enum.hpp>
#include <map>

HTTPRequest::HTTPRequest() :
		m_version(),
		m_url(),
		m_headers(),
		m_method(),
		m_serverBlock(),
		m_locationBlock(),
		m_resource()
{
}

HTTPRequest::HTTPRequest(const HTTPVersion &version, const URL &url, const HTTPHeaderFields &headers) :
		m_version(version),
		m_url(url),
		m_headers(headers),
		m_method(),
		m_serverBlock(),
		m_locationBlock(),
		m_resource(url.path())
{
}

HTTPRequest::HTTPRequest(const HTTPRequest &other) :
		m_version(other.m_version),
		m_url(other.m_url),
		m_headers(other.m_headers),
		m_method(other.m_method),
		m_serverBlock(other.m_serverBlock),
		m_locationBlock(other.m_locationBlock),
		m_resource(other.m_resource)
{
}

HTTPRequest::~HTTPRequest()
{
}

HTTPRequest&
HTTPRequest::operator=(const HTTPRequest &other)
{
	if (this != &other)
	{
		m_version = other.m_version;
		m_url = other.m_url;
		m_headers = other.m_headers;
		m_method = other.m_method;
		m_serverBlock = other.m_serverBlock;
		m_locationBlock = other.m_locationBlock;
		m_resource = other.m_resource;
	}

	return (*this);
}

const HTTPVersion&
HTTPRequest::version(void) const
{
	return (m_version);
}

const URL&
HTTPRequest::url(void) const
{
	return (m_url);
}

void
HTTPRequest::method(const HTTPMethod &method)
{
	m_method = &method;
}

Optional<const HTTPMethod*>
HTTPRequest::method(void) const
{
	return (Optional<const HTTPMethod*>::ofNullable(m_method));
}

void
HTTPRequest::serverBlock(const ServerBlock &serverBlock)
{
	m_serverBlock = &serverBlock;
}

Optional<const ServerBlock*>
HTTPRequest::serverBlock(void) const
{
	return (Optional<const ServerBlock*>::ofNullable(m_serverBlock));
}

void
HTTPRequest::locationBlock(const LocationBlock &locationBlock)
{
	m_locationBlock = &locationBlock;
}

const Optional<const LocationBlock*>
HTTPRequest::locationBlock(void) const
{
	return (Optional<const LocationBlock*>::ofNullable(m_locationBlock));
}

HTTPHeaderFields&
HTTPRequest::headers()
{
	return (m_headers);
}

const std::string&
HTTPRequest::resource() const
{
	return (m_resource);
}

void
HTTPRequest::resource(const std::string &resource)
{
	m_resource = resource;
}

std::list<const HTTPMethod*>
HTTPRequest::allowedMethods()
{
	std::map<int, const HTTPMethod*> allowedMap;

	if (m_locationBlock && m_locationBlock->methods().present())
	{
		typedef std::list<std::string> list;

		const list &methods = m_locationBlock->methods().get();
		for (list::const_iterator it = methods.begin(); it != methods.end(); it++)
		{
			const HTTPMethod *methodPtr = HTTPMethod::find(*it);

			if (methodPtr)
				allowedMap[methodPtr->ordinal()] = methodPtr;
		}
	}

	if (m_serverBlock && m_serverBlock->methods().present())
	{
		typedef std::list<std::string> list;

		const list &methods = m_serverBlock->methods().get();
		for (list::const_iterator it = methods.begin(); it != methods.end(); it++)
		{
			const HTTPMethod *methodPtr = HTTPMethod::find(*it);

			if (methodPtr)
				allowedMap[methodPtr->ordinal()] = methodPtr;
		}
	}

	return (Collections::values<int, const HTTPMethod*>(allowedMap));
}

Optional<const AuthBlock*>
HTTPRequest::authBlock() const
{
	if (m_locationBlock && m_locationBlock->auth().present())
		return (m_locationBlock->auth().get());

	if (m_serverBlock && m_serverBlock->auth().present())
		return (m_serverBlock->auth().get());

	return (Optional<const AuthBlock*>());
}

File
HTTPRequest::targetFile()
{
	return (File(root(), m_resource));
}

std::string
HTTPRequest::root(void) const
{
	if (locationBlock().present())
	{
		const LocationBlock &locationBlock = *this->locationBlock().get();

		if (locationBlock.root().present())
			return (locationBlock.root().get());
	}

	if (serverBlock().present())
	{
		const ServerBlock &serverBlock = *this->serverBlock().get();

		if (serverBlock.root().present())
			return (serverBlock.root().get());
	}

	if (Configuration::instance().rootBlock().root().present())
		return (Configuration::instance().rootBlock().root().get());

	return (File::currentDirectory().path());
}

bool
HTTPRequest::listing() const
{
	if (m_locationBlock && m_locationBlock->listing().orElse(false))
		return (true);

	if (m_serverBlock && m_serverBlock->listing().orElse(false))
		return (true);

	return (false);
}

void
HTTPRequest::urlPath(const std::string & path)
{
	m_resource = path;
}