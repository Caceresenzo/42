/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBuffer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:38:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 22:38:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/SocketBuffer.hpp>
#include <algorithm>
#include <iostream>

SocketBuffer::SocketBuffer(Socket &socket, int actionOnDestroy, size_type maxSize) :
		FileDescriptorBuffer(socket, actionOnDestroy, maxSize)
{
}

SocketBuffer::~SocketBuffer()
{
}

ssize_t
SocketBuffer::recv(int flags, size_t len)
{
	size_t capacity;

	if (m_maxSize == std::string::npos)
		capacity = len;
	else
		capacity = this->capacity();

	if (!capacity)
		capacity = 1;

	char rbuffer[capacity];
	ssize_t r = static_cast<Socket&>(m_fd).recv(rbuffer, std::min(capacity, len), flags);

	if (r >= 0)
		BaseBuffer::store(rbuffer, r);

	m_readEverything = r == 0;

	return (r);
}

ssize_t
SocketBuffer::send(int flags, size_t len)
{
	ssize_t r = static_cast<Socket&>(m_fd).send(m_storage.data(), std::min(m_storage.length(), len), flags);

	if (r > 0)
		m_storage.erase(0, r);

	return (r);
}

SocketBuffer*
SocketBuffer::from(Socket &socket, int actionOnDestroy, size_type maxSize)
{
	return (new SocketBuffer(socket, actionOnDestroy, maxSize));
}
