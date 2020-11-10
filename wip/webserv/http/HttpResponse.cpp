/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:38:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 16:38:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cygwin/socket.h>
#include <exception/IOException.hpp>
#include <http/HttpResponse.hpp>
#include <http/HTTP.hpp>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <cstring>
#include <iostream>
#include <map>

#if 1
#include <sstream>
#endif

HttpResponse::StatusLine::StatusLine(void) :
		m_version(HTTPVersion::HTTP_1_1),
		m_status()
{
}

HttpResponse::StatusLine::StatusLine(const HTTPStatus &status) :
		m_version(HTTPVersion::HTTP_1_1),
		m_status(status)
{
}

HttpResponse::StatusLine::StatusLine(const HTTPVersion &version, const HTTPStatus &status) :
		m_version(version),
		m_status(status)
{
}

HttpResponse::StatusLine::StatusLine(const StatusLine &other) :
		m_version(other.m_version),
		m_status(other.m_status)
{
}

HttpResponse::StatusLine::~StatusLine()
{
}

HttpResponse::StatusLine&
HttpResponse::StatusLine::operator =(const StatusLine &other)
{
	if (this != &other)
	{
		m_version = other.m_version;
		m_status = other.m_status;
	}

	return (*this);
}

std::string
HttpResponse::StatusLine::format(void) const
{
	std::stringstream stream;

	stream << m_version.format() << HTTP::SP << m_status.code() << HTTP::SP << m_status.reasonPhrase();

	return (stream.str());
}

HttpResponse::IBody::~IBody()
{
}

HttpResponse::FileBody::FileBody(int fd) :
		m_fd(fd),
		m_size(0)
{
}

HttpResponse::FileBody::~FileBody()
{
	::close(m_fd);
}

ssize_t
HttpResponse::FileBody::write(int fd)
{
	if (m_size == 0)
	{
		ssize_t r = ::read(m_fd, m_buffer, sizeof(m_buffer));
		if (r > 0)
			m_size = r;

		if (r == -1)
			throw IOException("read");
	}

	ssize_t sent = ::send(fd, m_buffer, m_size, MSG_NOSIGNAL);
	if (sent > 0)
	{
		if (m_size != sent) {
			::memmove(m_buffer, m_buffer + sent, size_t(m_size - sent));
		}

		m_size -= sent;
	}

	if (sent == -1)
	{
		std::cout << IOException("sent", errno).what() << std::endl;
		std::cout << "sent: " << sent << std::endl;
		std::cout << "m_size: " << m_size << std::endl;
	}

	return (sent);
}

HttpResponse::StringBody::StringBody(std::string string) :
		m_string(string),
		m_index(0)
{
}

HttpResponse::StringBody::~StringBody()
{
}

ssize_t
HttpResponse::StringBody::write(int fd)
{
	ssize_t r = send(fd, m_string.c_str() + m_index, m_string.size() - m_index, 0);

	if (r > 0)
	{
		m_index += r;
	}

	return (r);
}

HttpResponse::HttpResponse(const HTTPVersion &version, const HTTPStatus &status, HTTPHeaderFields headers, IBody *body) :
		m_statusLine(version, status),
		m_headers(headers),
		m_body(body),
		m_state(NONE),
		m_state_index(-1)
{
}

HttpResponse::~HttpResponse()
{
	if (m_body)
		delete m_body;
}

ssize_t
HttpResponse::write(int fd)
{
	std::string str;
	HTTPHeaderFields::const_iterator it;
	HTTPHeaderFields::const_iterator ite;

	if (m_state == NONE)
		m_state = STATUS_LINE;

	switch (m_state)
	{
		case STATUS_LINE:
			m_state = HEADERS;
			str = m_statusLine.format() + HTTP::CRLF;
			return (::send(fd, str.c_str(), str.length(), 0));
			break;

		case HEADERS:
			m_state = EMPTY_LINE;

			it = m_headers.begin();
			ite = m_headers.end();

			while (it != ite)
			{
				str += it->first + std::string(": ") + it->second + HTTP::CRLF;
				it++;
			}

			return (::send(fd, str.c_str(), str.length(), 0));
			break;

		case EMPTY_LINE:
			m_state = BODY;

			str = HTTP::CRLF;

			return (::send(fd, str.c_str(), str.length(), 0));
			break;

		case BODY:
			if (m_body)
				return (m_body->write(fd));

			m_state = FINISHED;
			return (0);
			break;

		case FINISHED:
			return (0);
			break;

		default:
			break;
	}

	return (-1);
}
