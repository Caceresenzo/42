/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileBuffer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:24:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/17 18:24:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <algorithm>
#include <iostream>
#include <libs/ft.hpp>

FileDescriptorBuffer::FileDescriptorBuffer(FileDescriptor &fileDescriptor, int actionOnDestroy, size_type maxSize) :
		BaseBuffer(maxSize),
		m_fd(fileDescriptor),
		m_actionOnDestroy(actionOnDestroy),
		m_readEverything(false)
{
}

FileDescriptorBuffer::~FileDescriptorBuffer()
{
	if (m_actionOnDestroy & CLOSE)
		close();

	if (m_actionOnDestroy & DELETE)
		delete &m_fd;
}

ssize_t
FileDescriptorBuffer::read(size_t len)
{
	size_t capacity;

	if (m_maxSize == std::string::npos)
		capacity = len;
	else
		capacity = this->capacity();

	if (!capacity)
		capacity = 1;

	char rbuffer[capacity];
	ssize_t r = m_fd.read(rbuffer, std::min(capacity, len));

	if (r >= 0)
		BaseBuffer::store(rbuffer, r);

	m_readEverything = r == 0;

	return (r);
}

ssize_t
FileDescriptorBuffer::write(size_t len)
{
	ssize_t r = m_fd.write(m_storage.data(), std::min(m_storage.length(), len));

	if (r > 0)
		m_storage.erase(0, r);

	return (r);
}

void
FileDescriptorBuffer::close(void)
{
	m_fd.close();
}

FileDescriptorBuffer*
FileDescriptorBuffer::from(FileDescriptor &fileDescriptor, int actionOnDestroy, size_type maxSize)
{
	return (new FileDescriptorBuffer(fileDescriptor, actionOnDestroy, maxSize));
}

ssize_t
FileDescriptorBuffer::storeZeros(size_t size)
{
		size_t capacity;

	if (m_maxSize == std::string::npos)
		capacity = size;
	else
		capacity = this->capacity();

	if (!capacity)
		capacity = 1;

	char rbuffer[capacity];
	ft::memset(rbuffer, '0', capacity);
	
	BaseBuffer::store(rbuffer, (int)capacity);
	
	m_readEverything = size == capacity;
	
	return (capacity);
}