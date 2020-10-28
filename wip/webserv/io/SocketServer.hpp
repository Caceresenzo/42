/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:01:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:01:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETSERVER_HPP_
# define SOCKETSERVER_HPP_

# include <io/Socket.hpp>

class SocketServer :
		public Closable
{
	public:
		static const int DEFAULT_BACKLOG;

	private:
		int m_port;
		int m_backlog;
		Socket m_socket;

	public:
		SocketServer(void);
		SocketServer(const SocketServer &other);

		virtual
		~SocketServer();

		void
		reusable(void) throw (IOException);

		void
		bind(int port) throw (IOException);

		void
		listen(void) throw (IOException);

		void
		listen(int backlog) throw (IOException);

		Socket
		accept() const throw (IOException);

		void
		close() throw (IOException);

		int
		port() const;

		int
		backlog() const;

		int
		fd() const;
};

#endif /* SOCKETSERVER_HPP_ */
