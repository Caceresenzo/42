/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileResponseBody.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:14:47 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 17:14:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <http/response/body/impl/FileResponseBody.hpp>
#include <util/Singleton.hpp>

FileResponseBody::FileResponseBody(FileDescriptorBuffer &fdBuffer) :
		m_fdBuffer(fdBuffer)
{
	NIOSelector::instance().add(m_fdBuffer.descriptor(), *this, NIOSelector::READ);
}

FileResponseBody::~FileResponseBody()
{
	NIOSelector::instance().remove(m_fdBuffer.descriptor());

	delete &m_fdBuffer;
}

bool
FileResponseBody::store(BaseBuffer &buffer)
{
	buffer.store(m_fdBuffer);

	return (isDone());
}

bool
FileResponseBody::readable(FileDescriptor &fd)
{
	(void)fd;

	m_fdBuffer.read(); // TODO Need check

	return (isDone());
}

bool
FileResponseBody::isDone()
{
	return (m_fdBuffer.hasReadEverything() && m_fdBuffer.empty());
}
