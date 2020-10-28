/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:18:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/20 13:18:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HttpRequest.hpp>
#include <sstream>

HttpRequest::HttpRequest()
{
}

HttpRequest::HttpRequest(const Socket &socket) :
		m_socket(socket)
{
}

HttpRequest::HttpRequest(const HttpRequest &other) :
		m_socket(other.m_socket),
		m_raw(other.m_raw),
		m_headers(other.m_headers)
{
}

HttpRequest::~HttpRequest()
{
}

HttpRequest&
HttpRequest::operator =(const HttpRequest &other)
{
	if (this != &other)
	{
		m_socket = other.m_socket;
		m_raw = other.m_raw;
		m_headers = other.m_headers;
	}

	return (*this);
}

bool
HttpRequest::read(void)
{
	char buff[2000] = { 0 };
	ssize_t len = recv(m_socket.fd(), buff, sizeof(buff) - 1, 0);

	if (len == -1)
		return (true);

	if (len == 0)
		return (true);

	m_raw += buff;
	size_t pos;
	while ((pos = m_raw.find('\n')) != size_t(-1))
	{

		std::istringstream iss(m_raw);
		std::string line;
		std::getline(iss, line);

		if (m_head.empty())
			m_head = line;
		else
		{
			std::cout << line << std::endl;
		}

		m_raw = m_raw.substr(pos + 1);
	}

	return (false);
}

bool
HttpRequest::write(void)
{
	return (true);
}

void
HttpRequest::setHeader(const std::string &name, const std::string &value)
{
	m_headers[name] = value;
}

bool
HttpRequest::getHeader(const std::string &name, std::string &value)
{
	std::map<std::string, std::string>::iterator it = m_headers.find(name);

	if (it != m_headers.end())
	{
		value = it->second;
		return (true);
	}

	return (false);
}
