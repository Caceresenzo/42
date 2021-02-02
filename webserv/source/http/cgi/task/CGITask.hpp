/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGITask.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:41:54 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 16:41:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGITASK_HPP_
# define CGITASK_HPP_

#include <http/parser/HTTPHeaderFieldsParser.hpp>
#include <http/task/HTTPTask.hpp>
#include <io/FileDescriptor.hpp>
#include <nio/NIOSelector.hpp>
#include <stddef.h>

class CommonGatewayInterface;
class HTTPClient;

class CGITask :
		public HTTPTask,
		public NIOSelector::Callback
{
	public:
		static Logger &LOG;

	private:
		HTTPClient &m_client;
		CommonGatewayInterface &m_cgi;
		FileDescriptorBuffer &m_bufferedOut;
		HTTPHeaderFieldsParser m_headerFieldsParser;
		size_t wroteBodyUpTo;
		bool m_running;
		bool m_nextCalled;

	private:
		CGITask();
		CGITask(const CGITask &other);

		CGITask&
		operator=(const CGITask &other);

	public:
		CGITask(HTTPClient &client, CommonGatewayInterface &cgi);

		virtual
		~CGITask();

		bool
		running();

		bool
		writable(FileDescriptor &fd);

		bool
		readable(FileDescriptor &fd);

		bool
		isDone();

		bool
		hasReadHeaders();

		FileDescriptorBuffer&
		out();

		bool
		timeoutTouch();
};

#endif /* CGITASK_HPP_ */
