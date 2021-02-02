/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponseBody.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:24:51 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 10:23:40 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIRESPONSEBODY_HPP_
# define CGIRESPONSEBODY_HPP_

#include <buffer/impl/BaseBuffer.hpp>
#include <http/response/body/IResponseBody.hpp>
#include <nio/NIOSelector.hpp>

class CGITask;
class HTTPClient;

class CGIResponseBody :
		public IResponseBody,
		public NIOSelector::Callback
{
	private:
		HTTPClient &m_client;
		CGITask &m_task;

	private:
		CGIResponseBody();
		CGIResponseBody(const CGIResponseBody &other);

		CGIResponseBody&
		operator=(const CGIResponseBody &other);

	public:
		CGIResponseBody(HTTPClient &client, CGITask &task);

		virtual
		~CGIResponseBody();

		bool
		isSelfManaged() const;

		bool
		store(BaseBuffer &buffer);
};

#endif /* CGIRESPONSEBODY_HPP_ */
