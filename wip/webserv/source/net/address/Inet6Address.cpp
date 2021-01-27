/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inet6Address.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:47:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 20:47:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <net/address/Inet6Address.hpp>
#include <util/Convert.hpp>
#include <iostream>

Inet6Address::Inet6Address() :
		m_address()
{
	ft::bzero(m_address, sizeof(m_address));
}

Inet6Address::Inet6Address(byte address[16]) :
		m_address()
{
	ft::memcpy(m_address, address, sizeof(m_address));
}

Inet6Address::Inet6Address(ushort a, ushort b, ushort c, ushort d, ushort e, ushort f, ushort g, ushort h) :
		m_address()
{
	m_address[0] = a & 0xff;
	m_address[1] = (a >> 8) & 0xff;
	m_address[2] = b & 0xff;
	m_address[3] = (b >> 8) & 0xff;
	m_address[4] = c & 0xff;
	m_address[5] = (c >> 8) & 0xff;
	m_address[6] = d & 0xff;
	m_address[7] = (d >> 8) & 0xff;
	m_address[8] = e & 0xff;
	m_address[9] = (e >> 8) & 0xff;
	m_address[10] = f & 0xff;
	m_address[11] = (f >> 8) & 0xff;
	m_address[12] = g & 0xff;
	m_address[13] = (g >> 8) & 0xff;
	m_address[14] = h & 0xff;
	m_address[15] = (h >> 8) & 0xff;
}

Inet6Address::Inet6Address(const Inet6Address &other) :
		m_address()
{
	ft::memcpy(m_address, other.m_address, sizeof(m_address));
}

Inet6Address::~Inet6Address()
{
}

Inet6Address&
Inet6Address::operator =(const Inet6Address &other)
{
	if (this != &other)
		ft::memcpy(m_address, other.m_address, sizeof(m_address));

	return (*this);
}

std::vector<byte>
Inet6Address::address() const
{
	return (std::vector<byte>(m_address, m_address + sizeof(m_address)));
}

std::string
Inet6Address::hostAddress() const
{
	const ushort *address = (const ushort*)m_address;

	std::string out;
	for (int i = 0; i < 8; i++)
	{
		out += Convert::toString(address[i], 16);

		if (i + 1 < 8)
			out += ':';
	}

	return (out);
}

InetAddress*
Inet6Address::clone() const
{
	return (new Inet6Address(*this));
}
