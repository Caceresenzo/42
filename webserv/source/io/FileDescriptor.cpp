/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:02:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/17 18:02:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IOException.hpp>
#include <io/FileDescriptor.hpp>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <iostream>

FileDescriptor::FileDescriptor(int fd) :
		m_fd(fd),
		m_verified(false),
		m_closed(false)
{
}

FileDescriptor::~FileDescriptor()
{
	if (m_verified && !m_closed)
		::close(m_fd);
}

ssize_t
FileDescriptor::read(void *buf, size_t nbyte)
{
	ensureNotClosed();

	ssize_t r = ::read(m_fd, buf, nbyte);

#ifdef IO_FILEDESCRIPTOR_DEBUG_READ
	std::cout << m_fd << ": read()= " << r << std::endl;
#endif

	if (!m_verified && r != -1)
		m_verified = true;

	return (r);
}

ssize_t
FileDescriptor::write(const void *buf, size_t nbyte)
{
	ensureNotClosed();

	ssize_t r = ::write(m_fd, buf, nbyte);

#ifdef IO_FILEDESCRIPTOR_DEBUG_WRITE
	std::cout << m_fd << ": write()= " << r << std::endl;
#endif

	if (!m_verified && r != -1)
		m_verified = true;

	return (r);
}

off_t
FileDescriptor::lseek(off_t offset, int whence)
{
	ensureNotClosed();

	return (::lseek(m_fd, offset, whence));
}

off_t
FileDescriptor::seekToEnd()
{
	off_t position = lseek(0, SEEK_END);

	if (position == off_t(-1))
		throw IOException("lseek(end)", errno);

	off_t r = lseek(position, SEEK_SET);

	if (r == off_t(-1))
		throw IOException("lseek(set)", errno);

	return (r);
}

void
FileDescriptor::close()
{
	ensureNotClosed();

	if (!m_closed)
	{
		::close(m_fd);

		m_closed = true;
	}
}

void
FileDescriptor::nonBlocking()
{
	if (::fcntl(m_fd, F_SETFL, O_NONBLOCK) == -1)
		throw IOException("fcntl", errno);

	m_verified = true;
}

int
FileDescriptor::raw() const
{
	return (m_fd);
}

bool
FileDescriptor::isClosed() const
{
	return (m_closed);
}

FileDescriptor*
FileDescriptor::wrap(int fd)
{
	FileDescriptor *fileDescriptor = new FileDescriptor(fd);

	try
	{
		fileDescriptor->nonBlocking();
	}
	catch (...)
	{
		delete fileDescriptor;

		throw;
	}

	return (fileDescriptor);
}
