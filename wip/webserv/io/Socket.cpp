/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 14:33:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IOException.hpp>
#include <io/Socket.hpp>
#include <util/Convert.hpp>
#include <sys/errno.h>
#include <unistd.h>
#include <cstring>
#include <string>

static const int g_true = 1;

Socket::Socket(void) :
		m_fd(-1)
{
}

Socket::Socket(int fd) :
		m_fd(fd)
{
}

Socket::Socket(const Socket &other) :
		m_fd(other.m_fd),
		m_addr(other.m_addr)
{
}

Socket::~Socket()
{
}

Socket&
Socket::operator =(const Socket &other)
{
	if (this != &other)
	{
		m_fd = other.m_fd;
		m_addr = other.m_addr;
	}

	return (*this);
}

void
Socket::bind(int port)
{
	memset(&m_addr, 0, sizeof(m_addr));

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_addr.sin_port = htons(port);

	if (::bind(m_fd, (struct sockaddr*)&m_addr, sizeof(m_addr)) == -1)
		throw IOException("bind(" + Convert::toString(port) + ")", errno);
}

void
Socket::close() throw (IOException)
{
	::close(m_fd);
}

void
Socket::reusable()
{
	if (::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &g_true, sizeof(int)) == -1)
		throw IOException("bind", errno);
}

int
Socket::fd() const
{
	return (m_fd);
}
