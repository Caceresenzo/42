/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIResponseBody.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:24:51 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 10:29:37 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <http/body/encoding/chunked/ChunkEncoder.hpp>
#include <http/cgi/task/CGITask.hpp>
#include <http/HTTPClient.hpp>
#include <http/response/body/impl/CGIResponseBody.hpp>

CGIResponseBody::CGIResponseBody(HTTPClient &client, CGITask &task) :
		m_client(client),
		m_task(task)
{
}

CGIResponseBody::~CGIResponseBody()
{
}

bool
CGIResponseBody::isSelfManaged() const
{
	return (true);
}

bool
CGIResponseBody::store(BaseBuffer &buffer)
{
	if (m_task.hasReadHeaders())
		return (false);

	bool hasResponseBody = m_client.request().method().get() != HTTPMethod::HEAD;

	if (hasResponseBody)
		buffer.store(m_task.out(), true, ChunkEncoder::staticEncode);

	if (m_task.isDone())
	{
		if (hasResponseBody)
			buffer.store(ChunkEncoder::ZERO);

		return (true);
	}

	return (false);
	
}
