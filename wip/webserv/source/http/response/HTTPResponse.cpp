/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:51:19 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:41:14 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HTTP.hpp>
#include <http/response/body/impl/CGIResponseBody.hpp>
#include <http/response/body/impl/StringResponseBody.hpp>
#include <http/response/HTTPResponse.hpp>
#include <http/response/HTTPStatusLine.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <string>

HTTPResponse::HTTPResponse() :
		m_status(),
		m_headers(),
		m_body(),
		m_ended(false),
		m_state(S_NONE)
{
}

HTTPResponse::HTTPResponse(const HTTPResponse &other) :
		m_status(other.m_status),
		m_headers(other.m_headers),
		m_body(other.m_body),
		m_ended(other.m_ended),
		m_state(other.m_state)
{
}

HTTPResponse::~HTTPResponse()
{
	DeleteHelper::pointer(m_body);
}

HTTPResponse&
HTTPResponse::operator=(const HTTPResponse &other)
{
	if (this != &other)
	{
		DeleteHelper::pointer(m_body);

		m_status = other.m_status;
		m_headers = other.m_headers;
		m_body = other.m_body;
		m_ended = other.m_ended;
		m_state = other.m_state;
	}

	return (*this);
}

void
HTTPResponse::status(const HTTPStatus &status)
{
	m_status.set(&status);
}

Optional<const HTTPStatus*>&
HTTPResponse::status()
{
	return (m_status);
}

HTTPHeaderFields&
HTTPResponse::headers()
{
	return (m_headers);
}

void
HTTPResponse::body(IResponseBody *body, bool deletePrevious)
{
	if (deletePrevious && m_body)
		delete m_body;

	m_body = body;
}

IResponseBody*
HTTPResponse::body()
{
	return (m_body);
}

void
HTTPResponse::end()
{
	m_ended = true;
}

bool
HTTPResponse::ended()
{
	return (m_ended);
}

bool
HTTPResponse::store(BaseBuffer &buffer)
{
	if (!m_ended)
		return (false);

	switch (m_state)
	{
		case S_NONE:
			m_state = S_HEADERS;

		case S_HEADERS:
		{
			buffer.store(HTTPStatusLine(*status().get()).format());
			buffer.store(HTTP::CRLF);
			buffer.store(headers().format());
			buffer.store(HTTP::CRLF);

			if (!m_body)
				return (true);

			m_state = S_BODY;

			return (false);
		}

		case S_BODY:
		{
			if (m_body->store(buffer))
				m_state = S_FLUSH;

			return (false);
		}

		case S_FLUSH:
			return (buffer.empty());
	}

	return (false); /* Should not happen. */
}

void
HTTPResponse::string(const std::string &content)
{
	body(new StringResponseBody(content));
	headers().contentLength(content.length());
	end();
}
