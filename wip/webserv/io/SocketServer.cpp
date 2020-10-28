/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:01:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:01:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IOException.hpp>
#include <io/Socket.hpp>
#include <io/SocketServer.hpp>
#include <stddef.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/socket.h>

const int SocketServer::DEFAULT_BACKLOG = 50;

SocketServer::SocketServer(void) :
		m_port(-1),
		m_backlog(0)
{
}

SocketServer::SocketServer(const SocketServer &other) :
		m_port(other.m_port),
		m_backlog(other.m_backlog),
		m_socket(other.m_socket)
{
}

SocketServer::~SocketServer()
{
}

void
SocketServer::reusable(void) throw (IOException)
{
	m_socket.reusable();
}

void
SocketServer::bind(int port) throw (IOException)
{
	m_socket = Socket(::socket(AF_INET, SOCK_STREAM, 0));
	if (m_socket.fd() == -1)
		throw IOException("socket", errno);

	m_socket.bind(port);
	m_port = port;
}

void
SocketServer::listen(void) throw (IOException)
{
	return (listen(DEFAULT_BACKLOG));
}

void
SocketServer::listen(int backlog) throw (IOException)
{
	if (::listen(m_socket.fd(), backlog) == -1)
		throw IOException("listen", errno);
}

Socket
SocketServer::accept() const throw (IOException)
{
	int accepted = ::accept(m_socket.fd(), NULL, NULL);

	if (accepted < 0)
		throw IOException("accept", errno);

	if (::fcntl(accepted, F_SETFL, O_NONBLOCK) == -1)
		throw IOException("fcntl", errno);

	return (Socket(accepted));
}

void
SocketServer::close() throw (IOException)
{
	IOException::check();
}

int
SocketServer::port() const
{
	return (m_port);
}

int
SocketServer::backlog() const
{
	return (m_backlog);
}

int
SocketServer::fd() const
{
	return (m_socket.fd());
}
