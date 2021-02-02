/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileResponseBody.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:14:47 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 14:19:44 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <http/response/body/impl/FileResponseBody.hpp>
#include <util/Singleton.hpp>
#include <iostream>

FileResponseBody::FileResponseBody(FileDescriptorBuffer &fdBuffer, size_t contentLength) :
		m_fdBuffer(fdBuffer),
		m_contentLength(contentLength),
		m_stored(0)
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

	ssize_t r = m_fdBuffer.read();
	if (r != -1)
		m_stored += r;
	else
	{	
		size_t diff = m_contentLength - m_stored;
		if (diff)
			m_stored += m_fdBuffer.storeZeros(diff);
	}	
	
	return (r <= 0 || isDone());
}

bool
FileResponseBody::isDone()
{
	return (m_fdBuffer.hasReadEverything() && m_fdBuffer.empty());
}
