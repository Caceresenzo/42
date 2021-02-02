/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InetSocketAddress.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:11:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 21:11:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <sys/socket.h>
#include <exception/Exception.hpp>
#include <net/address/Inet4Address.hpp>
#include <net/address/Inet6Address.hpp>
#include <net/address/InetSocketAddress.hpp>
#include <util/Byte.hpp>
#include <util/Convert.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <string>

InetSocketAddress::InetSocketAddress() :
		m_address(),
		m_port(0)
{
}

InetSocketAddress::InetSocketAddress(port_t port) :
		m_address(),
		m_port(port)
{
}

InetSocketAddress::InetSocketAddress(const InetAddress &address, port_t port) :
		m_address(address.clone()),
		m_port(port)
{
}

InetSocketAddress::InetSocketAddress(const InetSocketAddress &other) :
		m_address(other.m_address != NULL ? other.m_address->clone() : NULL),
		m_port(other.m_port)
{
}

InetSocketAddress::~InetSocketAddress()
{
	DeleteHelper::pointer<InetAddress>(m_address);
}

InetSocketAddress&
InetSocketAddress::operator =(const InetSocketAddress &other)
{
	if (this != &other)
	{
		DeleteHelper::pointer<InetAddress>(m_address);

		m_address = other.m_address != NULL ? other.m_address->clone() : NULL;
		m_port = other.m_port;
	}

	return (*this);
}

InetAddress*
InetSocketAddress::address(void) const
{
	return (m_address);
}

std::string
InetSocketAddress::hostAddress() const
{
	std::string out;

	if (m_address)
	{
		bool is6 = dynamic_cast<Inet6Address*>(m_address) != NULL;

		if (is6)
			out += '[';

		out += m_address->hostAddress();

		if (is6)
			out += ']';
	}

	return (out + ":" + Convert::toString(m_port));
}

InetSocketAddress::port_t
InetSocketAddress::port(void) const
{
	return (m_port);
}

/**
 * @source https://stackoverflow.com/a/57780111/7292958
 */
InetSocketAddress
InetSocketAddress::from(const struct sockaddr *addr, socklen_t addrlen)
{
	(void)addrlen; /* Used for UNIX, but not supported here. */

	switch (addr->sa_family)
	{
		case AF_INET:
		{
			const struct sockaddr_in *addr_in = (const struct sockaddr_in*)addr;

			return (InetSocketAddress(Inet4Address::parse(addr_in->sin_addr.s_addr), addr_in->sin_port));
		}

		case AF_INET6:
		{
			const struct sockaddr_in6 *addr_in6 = (const struct sockaddr_in6*)addr;

			return (InetSocketAddress(Inet6Address((byte*)addr_in6->sin6_addr.s6_addr), addr_in6->sin6_port));
		}

		case AF_UNIX:
			throw Exception("UNIX Socket Domain not supported");

		default:
			throw Exception("Unknown family: " + Convert::toString(addr->sa_family));
	}
}
