/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeaderFields.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:39:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/24 12:44:50 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADERFIELDS_HPP_
# define HTTPHEADERFIELDS_HPP_

#include <http/enums/HTTPMethod.hpp>
#include <http/header/HTTPDate.hpp>
#include <http/HTTP.hpp>
#include <stddef.h>
#include <util/Optional.hpp>
#include <util/StringUtils.hpp>
#include <list>
#include <map>
#include <string>
#include <vector>

class MIME;
class MIMERegistry;
class URL;

class HTTPHeaderFields
{
	public:
		typedef std::list<std::string> list;
		typedef list::const_iterator lconst_iterator;

		typedef std::map<std::string, list, StringUtils::InsensitiveCompare> map;
		typedef map::const_iterator mconst_iterator;

	private:
		map m_storage;

	public:
		HTTPHeaderFields(void);
		HTTPHeaderFields(map storage);
		HTTPHeaderFields(const HTTPHeaderFields &other);

		virtual
		~HTTPHeaderFields();

		HTTPHeaderFields&
		operator=(const HTTPHeaderFields &other);

		inline bool
		operator ==(const HTTPHeaderFields &other) const
		{
			return (m_storage == other.m_storage);
		}

		HTTPHeaderFields&
		acceptCharsets(const std::string &value);

		HTTPHeaderFields&
		acceptLanguage(const std::string &value);

		HTTPHeaderFields&
		allow(const HTTPMethod &method);

		HTTPHeaderFields&
		allow(const std::vector<const HTTPMethod*> &methods);

		HTTPHeaderFields&
		allow(const std::list<const HTTPMethod*> &methods);

		HTTPHeaderFields&
		allow(const std::string &value);

		HTTPHeaderFields&
		authorization(const std::string &value);

		HTTPHeaderFields&
		authorization(const std::string &type, const std::string &credentials);

		HTTPHeaderFields&
		contentLanguage(const std::string &value);

		HTTPHeaderFields&
		contentLength(size_t length);

		HTTPHeaderFields&
		contentLocation(const std::string &value);

		HTTPHeaderFields&
		contentType(const MIMERegistry &registry, const std::string &extension);

		HTTPHeaderFields&
		contentType(const std::string &mimeType);

		HTTPHeaderFields&
		contentType(const MIME &mime);

		HTTPHeaderFields&
		contentType(const Optional<const MIME*> &optional);

		HTTPHeaderFields&
		date(void);

		HTTPHeaderFields&
		date(const HTTPDate &date);

		HTTPHeaderFields&
		date(const std::string &value);

		HTTPHeaderFields&
		host(const std::string &value);

		HTTPHeaderFields&
		lastModified(long seconds);

		HTTPHeaderFields&
		lastModified(const Time &time);

		HTTPHeaderFields&
		lastModified(const HTTPDate &date);

		HTTPHeaderFields&
		lastModified(const std::string &value);

		HTTPHeaderFields&
		location(const std::string &value);

		HTTPHeaderFields&
		location(const URL &url);

		HTTPHeaderFields&
		referer(const std::string &value);

		HTTPHeaderFields&
		retryAfter(size_t seconds);

		HTTPHeaderFields&
		retryAfter(const HTTPDate &date);

		HTTPHeaderFields&
		retryAfter(const std::string &value);

		HTTPHeaderFields&
		server(void);

		HTTPHeaderFields&
		server(const std::string &value);

		HTTPHeaderFields&
		transferEncoding(const std::vector<std::string> &encodings);

		HTTPHeaderFields&
		transferEncoding(const std::list<std::string> &encodings);

		HTTPHeaderFields&
		transferEncoding(const std::string &value);

		HTTPHeaderFields&
		chunkedTransferEncoding(void);

		HTTPHeaderFields&
		userAgent(const std::string &value);

		HTTPHeaderFields&
		wwwAuthenticate(const std::string &type);

		HTTPHeaderFields&
		wwwAuthenticate(const std::string &type, const std::string &realm);

		HTTPHeaderFields&
		wwwAuthenticate(const std::string &type, const Optional<std::string> realm);

		HTTPHeaderFields&
		connection(const std::string &value);

		HTTPHeaderFields&
		html(void);

		HTTPHeaderFields&
		httpMessage(void);

		HTTPHeaderFields&
		set(const std::string &key, const std::string &value, bool folding = false);

		HTTPHeaderFields&
		merge(const HTTPHeaderFields &headerFields);

		const Optional<std::string>
		get(const std::string &key) const;

		mconst_iterator
		begin(void) const;

		mconst_iterator
		end(void) const;

		std::string
		format(const std::string &seperator = HTTP::CRLF) const;

		bool
		empty(void) const;

		void
		clear();

		map&
		storage(void);

		const map&
		storage(void) const;

	public:
		static const std::string ACCEPT_CHARSETS;
		static const std::string ACCEPT_LANGUAGE;
		static const std::string ALLOW;
		static const std::string AUTHORIZATION;
		static const std::string CONTENT_LANGUAGE;
		static const std::string CONTENT_LENGTH;
		static const std::string CONTENT_LOCATION;
		static const std::string CONTENT_TYPE;
		static const std::string DATE;
		static const std::string HOST;
		static const std::string LAST_MODIFIED;
		static const std::string LOCATION;
		static const std::string REFERER;
		static const std::string RETRY_AFTER;
		static const std::string SERVER;
		static const std::string TRANSFER_ENCODING;
		static const std::string USER_AGENT;
		static const std::string WWW_AUTHENTICATE;
		static const std::string SET_COOKIE;
		static const std::string CONNECTION;
		static const std::string STATUS;

		static const std::string MIME_HTML;
		static const std::string MIME_HTTP;

		static const std::string CHUNKED;
		static const std::string CLOSE;
		static const std::string KEEP_ALIVE;
};

#endif /* HTTPHEADERFIELDS_HPP_ */
