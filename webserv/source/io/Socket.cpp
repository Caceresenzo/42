/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:05 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:10:18 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <exception/IOException.hpp>
#include <io/Socket.hpp>
#include <libs/ft.hpp>
#include <net/address/InetSocketAddress.hpp>
#include <sys/errno.h>
#include <sys/socket.h>
#include <util/helper/DeleteHelper.hpp>
#include <util/Convert.hpp>
#include <iostream>

static const int g_true = 1;

Socket::Socket(int fd) :
		FileDescriptor(fd)
{
	m_verified = true;
}

Socket::~Socket()
{
}

ssize_t
Socket::recv(void *buf, size_t len, int flags)
{
	ensureNotClosed();

	ssize_t r = ::recv(m_fd, buf, len, flags);

#ifdef IO_SOCKET_DEBUG_RECV
	std::cout << m_fd << ": recv()= " << r << std::endl;
#endif

	return (r);
}

ssize_t
Socket::send(const void *buf, size_t len, int flags)
{
	ensureNotClosed();

	ssize_t r = ::send(m_fd, buf, len, flags);

#ifdef IO_SOCKET_DEBUG_SEND
	std::cout << m_fd << ": send()= " << r << std::endl;
#endif

	return (r);
}

void
Socket::bind(int port)
{
	struct sockaddr_in addr;
	ft::bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	bind(addr);

}

void
Socket::bind(const std::string &host, int port)
{
	struct sockaddr_in addr;
	ft::bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_port = htons(port);

	bind(addr);
}

void
Socket::bind(const struct sockaddr_in &addr)
{
	ensureNotClosed();

	if (::bind(m_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		throw IOException("bind", errno);
}

void
Socket::reusable()
{
	ensureNotClosed();

	if (::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &g_true, sizeof(int)) == -1)
		throw IOException("setsockopt(SO_REUSEADDR)", errno);
}

void
Socket::listen(void)
{
	ensureNotClosed();

	return (listen(DEFAULT_BACKLOG));
}

void
Socket::listen(int backlog)
{
	ensureNotClosed();

	if (::listen(m_fd, backlog) == -1)
		throw IOException("listen", errno);
}

Socket*
Socket::accept(InetSocketAddress *socketAddress) const
{
	ensureNotClosed();

	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);

	int fd = ::accept(raw(), (struct sockaddr*)&addr, &len);
	if (fd == -1)
		throw IOException("accept", errno);

	if (socketAddress)
		*socketAddress = InetSocketAddress::from((struct sockaddr*)&addr, len);

	try
	{
		return (new Socket(fd));
	}
	catch (...)
	{
		DeleteHelper::pointer(socketAddress);

		throw;
	}
}

Socket*
Socket::create(void)
{
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1)
		throw IOException("socket", errno);

	return (new Socket(fd));
}
