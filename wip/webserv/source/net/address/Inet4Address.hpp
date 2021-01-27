/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inet4Address.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:46:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 20:46:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INET4ADDRESS_HPP_
# define INET4ADDRESS_HPP_

#include <net/address/InetAddress.hpp>
#include <util/Byte.hpp>
#include <string>
#include <vector>

class Inet4Address :
		public InetAddress
{
	private:
		byte m_address[4];

	public:
		Inet4Address();
		Inet4Address(byte address[4]);
		Inet4Address(byte a, byte b, byte c, byte d);
		Inet4Address(const Inet4Address &other);

		virtual
		~Inet4Address();

		Inet4Address&
		operator=(const Inet4Address &other);

		std::vector<byte>
		address() const;

		std::string
		hostAddress() const;

		InetAddress*
		clone() const;

	public:
		static Inet4Address
		parse(unsigned int x);

		static bool
		validate(const std::string &text);
};

#endif /* INET4ADDRESS_HPP_ */
