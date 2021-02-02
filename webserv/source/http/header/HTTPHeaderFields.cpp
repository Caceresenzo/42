/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeaderFields.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:39:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 17:16:41 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/header/HTTPHeaderFields.hpp>
#include <http/mime/MIME.hpp>
#include <http/mime/MIMERegistry.hpp>
#include <util/Convert.hpp>
#include <util/Enum.hpp>
#include <util/Time.hpp>
#include <util/URL.hpp>
#include <webserv.hpp>
#include <set>

const std::string HTTPHeaderFields::ACCEPT_CHARSETS/*	*/= "Accept-Charsets";
const std::string HTTPHeaderFields::ACCEPT_LANGUAGE/*	*/= "Accept-Language";
const std::string HTTPHeaderFields::ALLOW/*				*/= "Allow";
const std::string HTTPHeaderFields::AUTHORIZATION/*		*/= "Authorization";
const std::string HTTPHeaderFields::CONTENT_LANGUAGE/*	*/= "Content-Language";
const std::string HTTPHeaderFields::CONTENT_LENGTH/*	*/= "Content-Length";
const std::string HTTPHeaderFields::CONTENT_LOCATION/*	*/= "Content-Location";
const std::string HTTPHeaderFields::CONTENT_TYPE/*		*/= "Content-Type";
const std::string HTTPHeaderFields::DATE/*				*/= "Date";
const std::string HTTPHeaderFields::HOST/*				*/= "Host";
const std::string HTTPHeaderFields::LAST_MODIFIED/*		*/= "Last-Modified";
const std::string HTTPHeaderFields::LOCATION/*			*/= "Location";
const std::string HTTPHeaderFields::REFERER/*			*/= "Referer";
const std::string HTTPHeaderFields::RETRY_AFTER/*		*/= "Retry-After";
const std::string HTTPHeaderFields::SERVER/*			*/= "Server";
const std::string HTTPHeaderFields::TRANSFER_ENCODING/*	*/= "Transfer-Encoding";
const std::string HTTPHeaderFields::USER_AGENT/*		*/= "User-Agent";
const std::string HTTPHeaderFields::WWW_AUTHENTICATE/*	*/= "WWW-Authenticate";
const std::string HTTPHeaderFields::SET_COOKIE/*	    */= "Set-Cookie";
const std::string HTTPHeaderFields::CONNECTION/*	    */= "Connection";
const std::string HTTPHeaderFields::STATUS/*	        */= "Status";

const std::string HTTPHeaderFields::MIME_HTML/*	        */= "text/html";
const std::string HTTPHeaderFields::MIME_HTTP/*	        */= "message/http";

const std::string HTTPHeaderFields::CHUNKED/*	        */= "chunked";
const std::string HTTPHeaderFields::CLOSE/*	            */= "close";
const std::string HTTPHeaderFields::KEEP_ALIVE/*	    */= "keep-alive";

HTTPHeaderFields::HTTPHeaderFields(void) :
		m_storage()
{
}

HTTPHeaderFields::HTTPHeaderFields(map storage) :
		m_storage(storage)
{
}

HTTPHeaderFields::HTTPHeaderFields(const HTTPHeaderFields &other) :
		m_storage(other.m_storage)
{
}

HTTPHeaderFields::~HTTPHeaderFields()
{
}

HTTPHeaderFields&
HTTPHeaderFields::operator=(const HTTPHeaderFields &other)
{
	if (this != &other)
		m_storage = other.m_storage;

	return (*this);
}

HTTPHeaderFields&
HTTPHeaderFields::acceptCharsets(const std::string &value)
{
	return (set(ACCEPT_CHARSETS, value));
}

HTTPHeaderFields&
HTTPHeaderFields::acceptLanguage(const std::string &value)
{
	return (set(ACCEPT_LANGUAGE, value));
}

HTTPHeaderFields&
HTTPHeaderFields::allow(const HTTPMethod &method)
{
	return (allow(method.name()));
}

HTTPHeaderFields&
HTTPHeaderFields::allow(const std::vector<const HTTPMethod*> &methods)
{
	if (methods.empty())
		return (*this);

	return (allow(Convert::join(methods)));
}

HTTPHeaderFields&
HTTPHeaderFields::allow(const std::list<const HTTPMethod*> &methods)
{
	if (methods.empty())
		return (*this);

	return (allow(Convert::join(methods)));
}

HTTPHeaderFields&
HTTPHeaderFields::allow(const std::string &value)
{
	return (set(ALLOW, value));
}

HTTPHeaderFields&
HTTPHeaderFields::authorization(const std::string &type, const std::string &credentials)
{
	return (authorization(type + " " + credentials));
}

HTTPHeaderFields&
HTTPHeaderFields::authorization(const std::string &value)
{
	return (set(AUTHORIZATION, value));
}

HTTPHeaderFields&
HTTPHeaderFields::contentLanguage(const std::string &value)
{
	return (set(CONTENT_LANGUAGE, value));
}

HTTPHeaderFields&
HTTPHeaderFields::contentLocation(const std::string &value)
{
	return (set(CONTENT_LOCATION, value));
}

HTTPHeaderFields&
HTTPHeaderFields::contentLength(size_t length)
{
	return (set(CONTENT_LENGTH, Convert::toString(length)));
}

HTTPHeaderFields&
HTTPHeaderFields::contentType(const MIMERegistry &registry, const std::string &extension)
{
	const MIME *mime = registry.findByFileExtension(extension);

	if (mime)
		return (contentType(*mime));

	return (*this);
}

HTTPHeaderFields&
HTTPHeaderFields::contentType(const std::string &mimeType)
{
	return (set(CONTENT_TYPE, mimeType));
}

HTTPHeaderFields&
HTTPHeaderFields::contentType(const MIME &mime)
{
	return (set(CONTENT_TYPE, mime.type()));
}

HTTPHeaderFields&
HTTPHeaderFields::contentType(const Optional<const MIME*> &optional)
{
	if (optional.absent())
		return (*this);

	return (set(CONTENT_TYPE, optional.get()->type()));
}

HTTPHeaderFields&
HTTPHeaderFields::date(void)
{
	return (date(HTTPDate::now()));
}

HTTPHeaderFields&
HTTPHeaderFields::date(const HTTPDate &date)
{
	return (this->date(date.format()));
}

HTTPHeaderFields&
HTTPHeaderFields::date(const std::string &value)
{
	return (set(DATE, value));
}

HTTPHeaderFields&
HTTPHeaderFields::host(const std::string &value)
{
	return (set(HOST, value));
}

HTTPHeaderFields&
HTTPHeaderFields::lastModified(long seconds)
{
	return (lastModified(Time(seconds)));
}

HTTPHeaderFields&
HTTPHeaderFields::lastModified(const Time &time)
{
	return (lastModified(HTTPDate(time)));
}

HTTPHeaderFields&
HTTPHeaderFields::lastModified(const HTTPDate &date)
{
	return (lastModified(date.format()));
}

HTTPHeaderFields&
HTTPHeaderFields::lastModified(const std::string &value)
{
	return (set(LAST_MODIFIED, value));
}

HTTPHeaderFields&
HTTPHeaderFields::location(const std::string &value)
{
	return (set(LOCATION, value));
}

HTTPHeaderFields&
HTTPHeaderFields::location(const URL &url)
{
	return (location(url.format()));
}

HTTPHeaderFields&
HTTPHeaderFields::referer(const std::string &value)
{
	return (set(REFERER, value));
}

HTTPHeaderFields&
HTTPHeaderFields::retryAfter(size_t seconds)
{
	return (retryAfter(Convert::toString(seconds)));
}

HTTPHeaderFields&
HTTPHeaderFields::retryAfter(const HTTPDate &date)
{
	return (retryAfter(date.format()));
}

HTTPHeaderFields&
HTTPHeaderFields::retryAfter(const std::string &value)
{
	return (set(RETRY_AFTER, value));
}

HTTPHeaderFields&
HTTPHeaderFields::server(void)
{
	return (server(APPLICATION_NAME));
}

HTTPHeaderFields&
HTTPHeaderFields::server(const std::string &value)
{
	return (set(SERVER, value));
}

HTTPHeaderFields&
HTTPHeaderFields::transferEncoding(const std::vector<std::string> &encodings)
{
	return (transferEncoding(Convert::join(encodings)));
}

HTTPHeaderFields&
HTTPHeaderFields::transferEncoding(const std::list<std::string> &encodings)
{
	return (transferEncoding(Convert::join(encodings)));
}

HTTPHeaderFields&
HTTPHeaderFields::transferEncoding(const std::string &value)
{
	return (set(TRANSFER_ENCODING, value));
}

HTTPHeaderFields&
HTTPHeaderFields::chunkedTransferEncoding(void)
{
	return (transferEncoding(CHUNKED));
}

HTTPHeaderFields&
HTTPHeaderFields::userAgent(const std::string &value)
{
	return (set(USER_AGENT, value));
}

HTTPHeaderFields&
HTTPHeaderFields::wwwAuthenticate(const std::string &type)
{
	return (set(WWW_AUTHENTICATE, type));
}

HTTPHeaderFields&
HTTPHeaderFields::wwwAuthenticate(const std::string &type, const std::string &realm)
{
	return (set(WWW_AUTHENTICATE, type + " realm=\"" + realm + "\""));
}

HTTPHeaderFields&
HTTPHeaderFields::wwwAuthenticate(const std::string &type, const Optional<std::string> realm)
{
	if (realm.present())
		return (wwwAuthenticate(type, realm.get()));

	return (wwwAuthenticate(type));
}

HTTPHeaderFields&
HTTPHeaderFields::connection(const std::string &value)
{
	return (set(CONNECTION, value));
}

HTTPHeaderFields&
HTTPHeaderFields::html(void)
{
	return (contentType(MIME_HTML));
}

HTTPHeaderFields&
HTTPHeaderFields::httpMessage(void)
{
	return (contentType(MIME_HTTP));
}

HTTPHeaderFields&
HTTPHeaderFields::set(const std::string &key, const std::string &value, bool folding)
{
	static std::string comaAndASpace = ", ";

	list &lst = m_storage[key];

	if (lst.empty() || key == SET_COOKIE)
		lst.push_back(value);
	else
	{
		if (folding)
			lst.front() += comaAndASpace + value; /* RFC 7230 - 3.2.2 */
		else
			lst.front() = value;
	}

	return (*this);
}

HTTPHeaderFields&
HTTPHeaderFields::merge(const HTTPHeaderFields &headerFields)
{
	for (mconst_iterator it = headerFields.begin(); it != headerFields.end(); it++)
		m_storage[it->first] = it->second;

	return (*this);
}

const Optional<std::string>
HTTPHeaderFields::get(const std::string &key) const
{
	mconst_iterator it = m_storage.find(key);

	if (it == m_storage.end())
		return (Optional<std::string>());

	return (Optional<std::string>::onlyIf(!it->second.empty(), it->second.front()));
}

HTTPHeaderFields::mconst_iterator
HTTPHeaderFields::begin(void) const
{
	return (m_storage.begin());
}

HTTPHeaderFields::mconst_iterator
HTTPHeaderFields::end(void) const
{
	return (m_storage.end());
}

std::string
HTTPHeaderFields::format(const std::string &separator) const
{
	static std::string colonAndASpace = ": ";

	std::string str;

	for (mconst_iterator it = begin(); it != end(); it++)
	{
		const list &lst = it->second;

		for (lconst_iterator lit = lst.begin(); lit != lst.end(); lit++)
			str += it->first + colonAndASpace + *lit + separator;
	}

	return (str);
}

bool
HTTPHeaderFields::empty(void) const
{
	return (m_storage.empty());
}

void
HTTPHeaderFields::clear(void)
{
	return (m_storage.clear());
}

HTTPHeaderFields::map&
HTTPHeaderFields::storage(void)
{
	return (m_storage);
}

const HTTPHeaderFields::map&
HTTPHeaderFields::storage(void) const
{
	return (m_storage);
}
