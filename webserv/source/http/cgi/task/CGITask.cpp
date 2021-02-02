/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGITask.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:41:55 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:33:14 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <exception/Exception.hpp>
#include <http/cgi/CommonGatewayInterface.hpp>
#include <http/cgi/task/CGITask.hpp>
#include <http/enums/HTTPMethod.hpp>
#include <http/enums/HTTPStatus.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/header/HTTPHeaderFields.hpp>
#include <http/HTTPClient.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/body/impl/CGIResponseBody.hpp>
#include <http/response/HTTPResponse.hpp>
#include <io/Socket.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <sys/types.h>
#include <util/Number.hpp>
#include <util/Optional.hpp>
#include <util/Singleton.hpp>
#include <iostream>
#include <string>

Logger &CGITask::LOG = LoggerFactory::get("CGI Task");

CGITask::CGITask(HTTPClient &client, CommonGatewayInterface &cgi) :
		m_client(client),
		m_cgi(cgi),
		m_bufferedOut(*FileDescriptorBuffer::from(m_cgi.out(), FileDescriptorBuffer::NOTHING)),
		wroteBodyUpTo(),
		m_running(true),
		m_nextCalled(false)
{
	if (m_client.request().method().get()->hasBody())
		NIOSelector::instance().add(m_cgi.in(), *this, NIOSelector::WRITE);
	else
		m_cgi.in().close();

	NIOSelector::instance().add(m_cgi.out(), *this, NIOSelector::READ);
}

CGITask::~CGITask()
{
	m_cgi.kill();

	NIOSelector::instance().remove(m_cgi.in());
	NIOSelector::instance().remove(m_cgi.out());

	delete &m_bufferedOut;
	delete &m_cgi;
}

bool
CGITask::running()
{
	return (m_running);
}

bool
CGITask::writable(FileDescriptor &fd)
{
	if (wroteBodyUpTo == m_client.body().length())
		return (true);

	ssize_t wrote = fd.write(m_client.body().c_str() + wroteBodyUpTo, m_client.body().length() - wroteBodyUpTo);

	if (wrote <= 0)
	{
		m_cgi.in().close();
		NIOSelector::instance().remove(m_cgi.in());
		return (true);
	}

	wroteBodyUpTo += wrote;
	if (wroteBodyUpTo == m_client.body().length())
	{
		m_cgi.in().close();
		NIOSelector::instance().remove(m_cgi.in());
		return (true);
	}

	return (false);
}

bool
CGITask::readable(FileDescriptor &fd)
{
	(void)fd;

	ssize_t r = m_bufferedOut.read();
	if (r == -1)
	{
		m_client.response().status(*HTTPStatus::INTERNAL_SERVER_ERROR);
		m_client.filterChain().next();

		NIOSelector::instance().update(m_client.socket(), NIOSelector::WRITE);
		return (true);
	}

	if (r == 0 && m_bufferedOut.empty() && m_headerFieldsParser.state() != HTTPHeaderFieldsParser::S_END)
	{
		m_client.response().status(*HTTPStatus::GATEWAY_TIMEOUT);

		m_nextCalled = true;
		m_client.filterChain().next();
		return (true);
	}

	if (m_headerFieldsParser.state() != HTTPHeaderFieldsParser::S_END)
	{
		char c;
		bool parsed = false;

		try
		{
			while (m_bufferedOut.next(c))
			{
				m_headerFieldsParser.consume(c);

				if (m_headerFieldsParser.state() == HTTPHeaderFieldsParser::S_END)
				{
					parsed = true;
					break;
				}
			}

			if (parsed)
			{
				m_client.response().headers().merge(m_headerFieldsParser.headerFields());

				Optional<std::string> statusOpt = m_headerFieldsParser.headerFields().get(HTTPHeaderFields::STATUS);
				if (statusOpt.present())
				{
					std::string codePart = statusOpt.get().substr(0, statusOpt.get().find(' '));

					int code = Number::parse<int>(codePart);
					const HTTPStatus *newStatus = HTTPStatus::find(code);

					if (newStatus)
						m_client.response().status(*newStatus);
				}

				m_client.response().headers().chunkedTransferEncoding();
				m_client.response().body(new CGIResponseBody(m_client, *this));

				m_nextCalled = true;
				m_client.filterChain().next();

				NIOSelector::instance().update(m_client.socket(), NIOSelector::WRITE);
			}

			return (false);
		}
		catch (Exception &exception)
		{
			LOG.warn() << "CGI produced an error: " << exception.message() << std::endl;

			m_client.response().status(*HTTPStatus::INTERNAL_SERVER_ERROR);

			m_nextCalled = true;
			m_client.filterChain().next();

			NIOSelector::instance().update(m_client.socket(), NIOSelector::WRITE);
			return (true);
		}
	}

	if (m_bufferedOut.hasReadEverything())
	{
		NIOSelector::instance().remove(m_cgi.out());
		return (true);
	}

	return (false);
}

bool
CGITask::isDone()
{
	return (m_bufferedOut.hasReadEverything() && m_bufferedOut.empty());
}

bool
CGITask::hasReadHeaders()
{
	return (m_headerFieldsParser.state() != HTTPHeaderFieldsParser::S_END);
}

FileDescriptorBuffer&
CGITask::out()
{
	return (m_bufferedOut);
}

bool
CGITask::timeoutTouch()
{
	if (m_running)
	{
		m_running = m_cgi.running();

		return (true);
	}

	return (false);
}
