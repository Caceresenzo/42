/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPOrchestrator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:34:10 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 15:18:20 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/RootBlock.hpp>
#include <config/block/ServerBlock.hpp>
#include <config/Configuration.hpp>
#include <exception/IOException.hpp>
#include <http/HTTPOrchestrator.hpp>
#include <io/Socket.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <nio/NIOSelector.hpp>
#include <sys/errno.h>
#include <util/FileDescriptorSet.hpp>
#include <util/Optional.hpp>
#include <util/Singleton.hpp>
#include <cstdio>
#include <iostream>
#include <new>
#include <string>

class NIOSelector;

Logger &HTTPOrchestrator::LOG = LoggerFactory::get("Orchestrator");

HTTPOrchestrator::HTTPOrchestrator(const server_container &servers) :
		m_servers(servers),
		m_running(false),
		m_stopping(false)
{
}

HTTPOrchestrator::~HTTPOrchestrator()
{
}

void
HTTPOrchestrator::prepare(void)
{
	for (server_iterator it = m_servers.begin(); it != m_servers.end(); it++)
	{
		try
		{
			HTTPServer &httpServer = *(*it);

			httpServer.start();
		}
		catch (...)
		{
			unprepare();

			throw;
		}
	}
}

void
HTTPOrchestrator::unprepare(void)
{
	for (server_iterator it = m_servers.begin(); it != m_servers.end(); it++)
		(*it)->close();
}

void
HTTPOrchestrator::start()
{
	prepare();

	for (server_iterator it = m_servers.begin(); it != m_servers.end(); it++)
	{
		HTTPServer &httpServer = *(*it);

		NIOSelector::instance().add(httpServer.socket(), httpServer, NIOSelector::ACCEPT);
	}

	try
	{
		FileDescriptorSet readSet;
		FileDescriptorSet writeSet;

		struct timeval timeout = {
			.tv_sec = 1,
			.tv_usec = 0 };

		LOG.info() << "Ready to accept connection!" << std::endl;

		m_running = true;
		while (m_running)
		{
			int fdCount;
			if ((fdCount = NIOSelector::instance().select(&readSet, &writeSet, &timeout)) == -1)
			{
				if (m_stopping && errno == EINTR)
					continue;

				NIOSelector::instance().debug(LOG, readSet, writeSet, true);

				throw IOException("select", errno);
			}

			if (fdCount)
				NIOSelector::instance().debug(LOG, readSet, writeSet, false);
			else if (m_stopping)
			{
				if (NIOSelector::instance().fds().empty())
				{
					m_running = false;
					break;
				}
			}

			for (server_iterator it = m_servers.begin(); it != m_servers.end(); it++)
				(*it)->watchForTimeouts();
		}
	}
	catch (Exception &exception)
	{
		LOG.error() << exception.message() << std::endl;
	}
	catch (std::bad_alloc &exception)
	{
		LOG.error() << exception.what() << std::endl;
	}

	m_running = false;

	while (!m_servers.empty())
	{
		server_iterator it = m_servers.begin();
		HTTPServer &httpServer = *(*it);

		try
		{
			NIOSelector::instance().remove(httpServer.socket());
			httpServer.close();
		}
		catch (Exception &exception)
		{
			LOG.error() << "Failed to terminate: " << httpServer.host() << ":" << httpServer.port() << ": " << exception.message() << std::endl;
		}

		delete &httpServer;

		m_servers.erase(it);
	}
}

void
HTTPOrchestrator::stop()
{
	m_stopping = true;

	for (server_iterator it = m_servers.begin(); it != m_servers.end(); it++)
		NIOSelector::instance().remove((*it)->socket());
}

HTTPOrchestrator*
HTTPOrchestrator::create()
{
	typedef std::map<short, std::list<ServerBlock const*> > port_map;
	typedef port_map::const_iterator port_iterator;

	typedef std::map<std::string, port_map> host_map;
	typedef host_map::const_iterator host_iterator;

	host_map hostToPortToServersMap;

	const RootBlock &rootBlock = Configuration::instance().rootBlock();

	const RootBlock::slist serverBlocks = rootBlock.serverBlocks().get();
	for (RootBlock::sciterator sit = serverBlocks.begin(); sit != serverBlocks.end(); sit++)
	{
		const ServerBlock &serverBlock = *(*sit);

		const std::string host = serverBlock.host().orElse(ServerBlock::DEFAULT_HOST);
		const short port = serverBlock.port().orElse(ServerBlock::DEFAULT_PORT);

		hostToPortToServersMap[host][port].push_back(&serverBlock);
	}

	server_container httpServers;
	for (host_iterator hit = hostToPortToServersMap.begin(); hit != hostToPortToServersMap.end(); hit++)
	{
		const std::string &host = hit->first;
		const port_map &portMap = hit->second;

		for (port_iterator pit = portMap.begin(); pit != portMap.end(); pit++)
		{
			short port = pit->first;
			const std::list<ServerBlock const*> &serverBlocks = pit->second;

			httpServers.push_back(new HTTPServer(host, port, serverBlocks));
		}
	}

	return (new HTTPOrchestrator(httpServers));
}
