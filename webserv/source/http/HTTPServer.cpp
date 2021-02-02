/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:33:42 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:05:12 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/RootBlock.hpp>
#include <config/Configuration.hpp>
#include <http/HTTPServer.hpp>
#include <http/task/HTTPTask.hpp>
#include <io/Socket.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <net/address/InetSocketAddress.hpp>
#include <util/Optional.hpp>
#include <util/Singleton.hpp>
#include <util/System.hpp>
#include <iostream>

Logger &HTTPServer::LOG = LoggerFactory::get("HTTP Server");

HTTPServer::HTTPServer(const std::string &host, short port, const std::list<ServerBlock const*> &serverBlocks) :
		m_host(host),
		m_port(port),
		m_serverBlocks(serverBlocks),
		m_socket(*Socket::create()),
		m_clients(),
		m_endingClients()
{
}

HTTPServer::~HTTPServer(void)
{
	delete &m_socket;
}

void
HTTPServer::start(void)
{
	m_socket.reusable();
	m_socket.nonBlocking();
	m_socket.bind(m_host, m_port);
	m_socket.listen();

	NIOSelector::instance().add(m_socket, *this, NIOSelector::ACCEPT);

	LOG.info() << "Listening on " << m_host << ":" << m_port << std::endl;
}

void
HTTPServer::close(void)
{
	m_socket.close();
}

void
HTTPServer::watchForTimeouts()
{
	typedef std::list<HTTPClient*> lst;

	if (m_clients.empty() && m_endingClients.empty())
		return;

	unsigned long now = System::currentTimeSeconds();
	unsigned long timeout = Configuration::instance().rootBlock().timeout().orElse(RootBlock::DEFAULT_TIMEOUT);

	for (lst::iterator it = m_clients.begin(); it != m_clients.end();)
	{
		HTTPClient &client = *(*it);
		it++;

		if (client.task() && client.task()->timeoutTouch())
			client.updateLastAction();
		else if (client.lastAction() + timeout < now)
		{
			if (LOG.isTraceEnabled())
				LOG.trace() << "Timeout-ed: " << client.socketAddress().hostAddress() << " (fd=" << client.socket().raw() << ")" << std::endl;

			delete &client;
		}
	}
}

Socket&
HTTPServer::socket(void)
{
	return (m_socket);
}

const Socket&
HTTPServer::socket(void) const
{
	return (m_socket);
}

const std::string&
HTTPServer::host(void) const
{
	return (m_host);
}

short
HTTPServer::port(void) const
{
	return (m_port);
}

const std::list<const ServerBlock*>&
HTTPServer::serverBlocks(void) const
{
	return (m_serverBlocks);
}

const ServerBlock*
HTTPServer::defaultServerBlock(void) const
{
	for (std::list<const ServerBlock*>::const_iterator it = m_serverBlocks.begin(); it != m_serverBlocks.end(); it++)
	{
		const ServerBlock &serverBlock = *(*it);

		if (serverBlock.isDefault().orElse(false))
			return (&serverBlock);
	}

	return (NULL);
}

bool
HTTPServer::readable(FileDescriptor &fd)
{
	Socket &serverSocket = static_cast<Socket&>(fd);

	InetSocketAddress socketAddress;
	Socket *socket = serverSocket.accept(&socketAddress);

	LOG.debug() << "Accepted: " << socketAddress.hostAddress() << " (fd=" << socket->raw() << ')' << std::endl;

	HTTPClient &httpClient = *(new HTTPClient(*socket, socketAddress, *this));
	m_clients.push_back(&httpClient);

	if (HTTPClient::INSTANCE_COUNT > Configuration::instance().rootBlock().maxActiveClient().orElse(RootBlock::DEFAULT_MAX_ACTIVE_CLIENT))
		HTTPClient::setUnavailable(httpClient);

	return (false);
}

void
HTTPServer::untrack(HTTPClient &client)
{
	m_clients.remove(&client);
	m_endingClients.remove(&client);
}

void
HTTPServer::ending(HTTPClient &client)
{
	delete &client;
}

HTTPServer::client_list::size_type
HTTPServer::tracked()
{
	return (m_clients.size());
}
