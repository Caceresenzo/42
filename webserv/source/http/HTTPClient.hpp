/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPClient.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:15:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 22:15:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCLIENT_HPP_
# define HTTPCLIENT_HPP_

#include <http/filter/FilterChain.hpp>
#include <http/parser/HTTPRequestParser.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <io/Socket.hpp>
#include <net/address/InetSocketAddress.hpp>
#include <nio/NIOSelector.hpp>
#include <string>

class HTTPTask;

# define HTTPCLIENT_LOG_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

class HTTPServer;
class Logger;
class SocketBuffer;

class HTTPClient :
		public NIOSelector::Callback
{
	public:
		enum State
		{
			S_NOT_STARTED = 0,
			S_HEADER,
			S_BODY,
			S_END,
		};

	public:
		static Logger &LOG;

	private:
		Socket &m_socket;
		InetSocketAddress m_socketAddress;
		SocketBuffer &m_in;
		SocketBuffer &m_out;
		HTTPServer &m_server;
		HTTPRequestParser m_parser;
		std::string m_body;
		State m_state;
		unsigned long m_lastAction;
		HTTPRequest m_request;
		HTTPResponse m_response;
		FilterChain m_filterChain;
		HTTPTask *m_task;
		bool m_keepAlive;

		HTTPClient(void);
		HTTPClient(const HTTPClient &other);

		HTTPClient&
		operator =(const HTTPClient &other);

	public:
		HTTPClient(Socket &socket, InetSocketAddress socketAddress, HTTPServer &server);

		virtual
		~HTTPClient();

		void
		log();

		void
		reset();

		void
		updateLastAction();

		inline Socket&
		socket(void)
		{
			return (m_socket);
		}

		inline const InetSocketAddress&
		socketAddress(void) const
		{
			return (m_socketAddress);
		}

		HTTPServer&
		httpServer()
		{
			return (m_server);
		}

		inline SocketBuffer&
		in()
		{
			return (m_in);
		}

		inline SocketBuffer&
		out()
		{
			return (m_out);
		}

		inline HTTPRequestParser&
		parser()
		{
			return (m_parser);
		}

		inline unsigned long&
		lastAction()
		{
			return (m_lastAction);
		}

		inline HTTPRequest&
		request(void)
		{
			return (m_request);
		}

		inline const HTTPRequest&
		request(void) const
		{
			return (m_request);
		}

		inline HTTPResponse&
		response(void)
		{
			return (m_response);
		}

		inline const HTTPResponse&
		response(void) const
		{
			return (m_response);
		}

		inline FilterChain&
		filterChain(void)
		{
			return (m_filterChain);
		}

		inline const FilterChain&
		filterChain(void) const
		{
			return (m_filterChain);
		}

		bool
		writable(FileDescriptor &fd);

		bool
		readable(FileDescriptor &fd);

		bool
		doRead();

		bool
		readHead(void);

		bool
		readBody(void);

		std::string&
		body();

		HTTPTask*
		task();

		void
		task(HTTPTask &task, bool removePrevious = true);

		void
		keepAlive(bool keepAlive);

	public:
		static void setUnavailable(HTTPClient &client);

	public:
		static int INSTANCE_COUNT;
};

#endif /* HTTPCLIENT_HPP_ */
