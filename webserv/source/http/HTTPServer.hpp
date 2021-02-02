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
#include <http/HTTPClient.hpp>
#include <io/FileDescriptor.hpp>
#include <nio/NIOSelector.hpp>
#include <list>
#include <string>

class Logger;
class HTTPClient;
class Socket;

class HTTPServer :
		public Closable,
		public NIOSelector::Callback
{
	public:
		typedef std::list<HTTPClient*> client_list;

	public:
		static Logger &LOG;

	private:
		std::string m_host;
		short m_port;
		std::list<ServerBlock const*> m_serverBlocks;
		Socket &m_socket;
		client_list m_clients;
		client_list m_endingClients;

	private:
		HTTPServer(void);
		HTTPServer(const HTTPServer &other);

		HTTPServer&
		operator=(const HTTPServer &other);

	public:
		HTTPServer(const std::string &host, short port, const std::list<ServerBlock const*> &serverBlocks);

		virtual
		~HTTPServer(void);

		void
		start(void);

		void
		close(void);

		void
		watchForTimeouts();

		Socket&
		socket(void);

		const Socket&
		socket(void) const;

		const std::string&
		host(void) const;

		short
		port(void) const;

		const std::list<const ServerBlock*>&
		serverBlocks(void) const;

		ServerBlock const*
		defaultServerBlock(void) const;

		void
		untrack(HTTPClient &client);

		void
		ending(HTTPClient &client);

		client_list::size_type
		tracked();

		bool
		readable(FileDescriptor &fd);
};

#endif /* HTTPSERVER_HPP_ */
