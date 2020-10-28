/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeaderFields.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:39:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 18:39:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADERFIELDS_HPP_
# define HTTPHEADERFIELDS_HPP_

#include <http/HTTPDate.hpp>
#include <http/HTTPMethod.hpp>
#include <http/mime/Mime.hpp>
#include <http/mime/MimeRegistry.hpp>
#include <stddef.h>
#include <iostream>
#include <list>
#include <map>
#include <vector>

class HTTPHeaderFields
{
	public:
		typedef std::map<std::string, std::string> map;
		typedef map::const_iterator const_iterator;

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

		HTTPHeaderFields&
		acceptCharsets(const std::string &value);

		HTTPHeaderFields&
		acceptLanguage(const std::string &value);

		HTTPHeaderFields&
		allow(const HTTPMethod &method);

		HTTPHeaderFields&
		allow(const std::vector<HTTPMethod> &methods);

		HTTPHeaderFields&
		allow(const std::list<HTTPMethod> &methods);

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
		contentType(const MimeRegistry &registry, const std::string &extension);

		HTTPHeaderFields&
		contentType(const std::string &mimeType);

		HTTPHeaderFields&
		contentType(const Mime &mime);

		HTTPHeaderFields&
		date(void);

		HTTPHeaderFields&
		date(const HTTPDate &date);

		HTTPHeaderFields&
		date(const std::string &value);

		HTTPHeaderFields&
		host(const std::string &value);

		HTTPHeaderFields&
		lastModified(const HTTPDate &date);

		HTTPHeaderFields&
		lastModified(const std::string &value);

		HTTPHeaderFields&
		location(const std::string &value);

		HTTPHeaderFields&
		referer(const std::string &value);

		HTTPHeaderFields&
		retryAfter(size_t seconds);

		HTTPHeaderFields&
		retryAfter(const HTTPDate &date);

		HTTPHeaderFields&
		retryAfter(const std::string &value);

		HTTPHeaderFields&
		server(const std::string &value);

		HTTPHeaderFields&
		transferEncoding(const std::vector<std::string> &encodings);

		HTTPHeaderFields&
		transferEncoding(const std::list<std::string> &encodings);

		HTTPHeaderFields&
		transferEncoding(const std::string &value);

		HTTPHeaderFields&
		userAgent(const std::string &value);

		HTTPHeaderFields&
		wwwAuthenticate(const std::string &value);

		HTTPHeaderFields&
		set(const std::string &key, const std::string &value);

		const_iterator
		begin(void) const;

		const_iterator
		end(void) const;

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
};

#endif /* HTTPHEADERFIELDS_HPP_ */
