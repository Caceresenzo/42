/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:33:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 14:33:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP_
# define HTTPSERVER_HPP_

#include <config/block/ServerBlock.hpp>
#include <io/SocketServer.hpp>
#include <vector>

class HTTPServer
{
	private:
		int m_port;
		std::vector<ServerBlock> m_servers;
		SocketServer m_socketServer;

	public:
		HTTPServer(void);
		HTTPServer(int port, const std::vector<ServerBlock> &servers);
		HTTPServer(const HTTPServer &other);

		virtual
		~HTTPServer();

		HTTPServer&
		operator=(const HTTPServer &other);

		void
		prepare(void);

		void
		unprepare(void);

		const SocketServer&
		serverSocket(void) const;
};

#endif /* HTTPSERVER_HPP_ */
