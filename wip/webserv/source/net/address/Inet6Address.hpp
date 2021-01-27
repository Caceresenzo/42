/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inet6Address.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:47:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 20:47:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INET6ADDRESS_HPP_
# define INET6ADDRESS_HPP_

#include <net/address/InetAddress.hpp>
#include <util/Byte.hpp>
#include <string>
#include <vector>

class Inet6Address :
		public InetAddress
{
	public:
		typedef unsigned short ushort;

	private:
		byte m_address[16];

	public:
		Inet6Address();
		Inet6Address(byte address[16]);
		Inet6Address(ushort a, ushort b, ushort c, ushort d, ushort e, ushort f, ushort g, ushort h);
		Inet6Address(const Inet6Address &other);

		virtual
		~Inet6Address();

		Inet6Address&
		operator=(const Inet6Address &other);

		std::vector<byte>
		address() const;

		std::string
		hostAddress() const;

		InetAddress*
		clone() const;
};

#endif /* INET6ADDRESS_HPP_ */
