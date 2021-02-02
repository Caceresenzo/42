/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutTask.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:55:50 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 10:43:31 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/handler/methods/task/PutTask.hpp>
#include <http/HTTPClient.hpp>
#include <http/response/HTTPResponse.hpp>
#include <util/Singleton.hpp>
#include <string>

PutTask::PutTask(HTTPClient &client, FileDescriptor &fileDescriptor, bool justCreated) :
		m_client(client),
		m_fileDescriptor(fileDescriptor),
		m_storedCount(0),
		m_justCreated(justCreated)
{
	NIOSelector::instance().add(fileDescriptor, *this, NIOSelector::WRITE);
}

PutTask::~PutTask()
{
	NIOSelector::instance().remove(m_fileDescriptor);
	delete &m_fileDescriptor;
}

bool
PutTask::running()
{
	if (m_storedCount == -1) /* error */
		return (true);

	return (static_cast<ssize_t>(m_client.body().size()) != m_storedCount);
}

bool
PutTask::writable(FileDescriptor &fd)
{
	ssize_t stored = fd.write(m_client.body().c_str() + m_storedCount, m_client.body().length() - m_storedCount);

	if (stored == -1)
	{
		m_storedCount = -1;
		this->~PutTask();
		m_client.response().status(*HTTPStatus::INTERNAL_SERVER_ERROR);
		m_client.filterChain().next();

		return (true);
	}
	else if (stored == 0 && m_storedCount == static_cast<ssize_t>(m_client.body().length()))
	{
		if (m_justCreated)
			m_client.response().status(*HTTPStatus::CREATED);
		else
			m_client.response().status(*HTTPStatus::OK);
		
		m_client.filterChain().next();

		return (true);
	}
	else
		m_storedCount += stored;

	return (false);
}
