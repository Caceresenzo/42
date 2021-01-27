/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InetSocketAddress.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:11:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 21:11:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INETSOCKETADDRESS_HPP_
# define INETSOCKETADDRESS_HPP_

#include <sys/socket.h>
#include <net/address/SocketAddress.hpp>

class InetAddress;

class InetSocketAddress :
		public SocketAddress
{
	public:
		typedef int port_t;

	private:
		InetAddress *m_address;
		port_t m_port;

	public:
		InetSocketAddress();
		InetSocketAddress(port_t port);
		InetSocketAddress(const InetAddress &address, port_t port);
		InetSocketAddress(const InetSocketAddress &other);

		virtual
		~InetSocketAddress();

		InetSocketAddress&
		operator=(const InetSocketAddress &other);

		InetAddress*
		address(void) const;

		std::string
		hostAddress() const;

		port_t
		port(void) const;

	public:
		static InetSocketAddress
		from(const struct sockaddr *addr, socklen_t addrlen);
};

#endif /* INETSOCKETADDRESS_HPP_ */
