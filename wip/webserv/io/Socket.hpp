/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:33:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 14:33:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <netinet/in.h>
#include <util/Closable.hpp>
# include <sys/socket.h>

class Socket :
		public Closable
{
	private:
		int m_fd;
		struct sockaddr_in m_addr;

	public:
		Socket(void);
		Socket(int fd);
		Socket(const Socket &other);

		virtual
		~Socket();

		Socket&
		operator=(const Socket &other);

		void
		bind(int port);

		void
		reusable();

		void
		close() throw (IOException);

		int
		fd() const;
};

#endif /* SOCKET_HPP_ */
