/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:05 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/19 21:32:18 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

#include <io/FileDescriptor.hpp>
#include <stddef.h>
#include <sys/types.h>
#include <string>

class InetSocketAddress;

class Socket :
		public FileDescriptor
{
	public:
		static const int DEFAULT_BACKLOG = 1000;

	private:
		Socket(void);
		Socket(int fd);
		Socket(const Socket &other);

		Socket&
		operator=(const Socket &other);

	public:
		virtual
		~Socket();

		ssize_t
		recv(void *buf, size_t len, int flags);

		ssize_t
		send(const void *buf, size_t len, int flags);

		void
		bind(int port);

		void
		bind(const std::string &host, int port);

		void
		bind(const struct sockaddr_in &addr);

		void
		reusable();

		void
		listen(void);

		void
		listen(int backlog);

		Socket*
		accept(InetSocketAddress *socketAddress) const;

	public:
		static Socket*
		create(void);
};

#endif /* SOCKET_HPP_ */
