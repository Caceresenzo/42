/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIOSelector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:38:08 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 09:46:38 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <nio/NIOSelector.hpp>
#include <sys/select.h>
#include <util/Collections.hpp>
#include <util/Convert.hpp>
#include <util/System.hpp>
#include <iostream>
#include <string>

Logger &NIOSelector::LOG = LoggerFactory::get("NIO Selector");

NIOSelector::NIOSelector() :
		m_fds(),
		m_read(),
		m_write(),
		m_highest(),
		m_operationConfig(),
		m_callbacks(),
		m_fileDescriptors()
{
}

NIOSelector::NIOSelector(const NIOSelector &other) :
		m_fds(other.m_fds),
		m_read(other.m_read),
		m_write(other.m_write),
		m_highest(other.m_highest),
		m_operationConfig(other.m_operationConfig),
		m_callbacks(other.m_callbacks),
		m_fileDescriptors(other.m_fileDescriptors)
{
}

NIOSelector::~NIOSelector()
{
}

NIOSelector&
NIOSelector::operator =(const NIOSelector &other)
{
	if (this != &other)
	{
		m_fds = other.m_fds;
		m_read = other.m_read;
		m_write = other.m_write;
		m_highest = other.m_highest;
		m_operationConfig = other.m_operationConfig;
		m_callbacks = other.m_callbacks;
		m_fileDescriptors = other.m_fileDescriptors;
	}

	return (*this);
}

void
NIOSelector::add(FileDescriptor &fd, Callback &callback, int operations)
{
	int raw = fd.raw();

	addToSets(fd.raw(), operations);

	m_callbacks[raw] = &callback;
	m_fileDescriptors[raw] = &fd;

	if (LOG.isTraceEnabled())
		LOG.trace() << "Added: " << raw << " (opts=" << operations << ")" << std::endl;
}

void
NIOSelector::update(FileDescriptor &fd, int operations)
{
	update(fd.raw(), operations);
}

void
NIOSelector::update(int fd, int operations)
{
	int opts = -42;
	if (LOG.isTraceEnabled())
		opts = this->operations(fd);

	if (removeFromSets(fd))
		addToSets(fd, operations);

	if (LOG.isTraceEnabled())
		LOG.trace() << "Updated: " << fd << " (from opts=" << opts << ", to opts=" << operations << ")" << std::endl;
}

void
NIOSelector::updateWithout(FileDescriptor &fd, int operations)
{
	updateWithout(fd.raw(), operations);
}

void
NIOSelector::updateWithout(int fd, int operations)
{
	int opts = this->operations(fd);

	if (opts != -1)
		update(fd, opts & ~operations);
}

void
NIOSelector::remove(FileDescriptor &fd)
{
	int opts = -42;
	if (LOG.isTraceEnabled())
		opts = operations(fd);

	if (removeFromSets(fd.raw()))
	{
		int raw = fd.raw();

		Collections::remove(m_operationConfig, raw);
		Collections::remove(m_callbacks, raw);
		Collections::remove(m_fileDescriptors, raw);

		if (LOG.isTraceEnabled())
			LOG.trace() << "Removed: " << fd.raw() << " (opts=" << opts << ")" << std::endl;
	}
	else
	{
		if (LOG.isTraceEnabled())
			LOG.trace() << "Not Removed: " << fd.raw() << std::endl;
	}
}

int
NIOSelector::select(FileDescriptorSet *read, FileDescriptorSet *write, struct timeval *timeout)
{
	fd_set *readSet = NULL;
	fd_set *writeSet = NULL;

	if (read)
	{
		*read = m_read;
		readSet = &read->storage();
	}

	if (write)
	{
		*write = m_write;
		writeSet = &write->storage();
	}

	int r = ::select(m_highest + 1, readSet, writeSet, NULL, timeout);

	if (r > 0)
	{
		if (read)
			for (int index = 0; index <= m_highest; index++)
			{
				if (read->test(index) && m_read.test(index))
				{
					FileDescriptor &fd = *m_fileDescriptors[index];

//					LOG.trace() << "Calling readable(" << index << ");" << std::endl;
					int r = m_callbacks[index]->readable(fd);
//					LOG.trace() << "Returned from readable(" << index << "); -> " << r << std::endl;

					if (r)
						updateWithout(index, ACCEPT | READ);
					// else if (r == -1)
					// 	m_callbacks[index]->response
				}
			}

		if (write)
			for (int index = 0; index <= m_highest; index++)
			{
				if (write->test(index) && m_write.test(index))
				{
					FileDescriptor &fd = *m_fileDescriptors[index];

//					LOG.trace() << "Calling writable(" << index << ");" << std::endl;
					bool r = m_callbacks[index]->writable(fd);
//					LOG.trace() << "Returned from writable(" << index << "); -> " << r << std::endl;

					if (r)
						updateWithout(index, WRITE);
				}
			}
	}

	return (r);
}

int
NIOSelector::operations(FileDescriptor &fd) const
{
	return (operations(fd.raw()));
}

int
NIOSelector::operations(int fd) const
{
	OperationConfigMap::const_iterator it = m_operationConfig.find(fd);
	if (it == m_operationConfig.end())
		return (-1);

	return (it->second);
}

const FileDescriptorSet&
NIOSelector::fds() const
{
	return (m_fds);
}

const FileDescriptorSet&
NIOSelector::readFds() const
{
	return (m_read);
}

const FileDescriptorSet&
NIOSelector::writeFds() const
{
	return (m_write);
}

void
NIOSelector::addToSets(int fd, int operations)
{
	if (operations & (ACCEPT | READ))
		m_read.set(fd);

	if (operations & (WRITE))
		m_write.set(fd);

	m_fds.set(fd);

	if (fd > m_highest)
		m_highest = fd;

	m_operationConfig[fd] = operations;
}

bool
NIOSelector::removeFromSets(int fd)
{
	int opts = operations(fd);

	if (opts != -1)
	{
		if (opts)
		{
			if (opts & (ACCEPT | READ))
				m_read.clear(fd);

			if (opts & (WRITE))
				m_write.clear(fd);
		}

		m_fds.clear(fd);

		if (fd == m_highest)
			recomputeHighestByDecreasing();

		return (true);
	}

	return (false);
}

NIOSelector::Callback::~Callback()
{
}

bool
NIOSelector::Callback::readable(FileDescriptor&)
{
	return (false);
}

bool
NIOSelector::Callback::writable(FileDescriptor&)
{
	return (false);
}

void
NIOSelector::debug(const Logger &logger, FileDescriptorSet &readFds, FileDescriptorSet &writeFds, bool forced)
{
	debug(logger, *this, readFds, writeFds, forced);
}

void
NIOSelector::recomputeHighestByDecreasing()
{
	while (m_highest >= 0 && !m_fds.test(m_highest))
		m_highest--;
}

void
NIOSelector::debug(const Logger &logger, const NIOSelector &selector, FileDescriptorSet &readFds, FileDescriptorSet &writeFds, bool forced)
{
	if (!logger.isDebugEnabled())
		return;

	static std::string last;
	static unsigned long lastTime = System::currentTimeSeconds();

	int highest = selector.m_highest + 3;

	std::string line;
	line.reserve(highest + 1);

	for (int i = 0; i < highest; i++)
	{
		char c = selector.fds().test(i) ? '-' : '.';

		bool canRead = readFds.test(i);
		bool canWrite = writeFds.test(i);

		if (canRead && canWrite)
			c = 'X';
		else if (canRead)
			c = 'R';
		else if (canWrite)
			c = 'W';

		line += c;
	}

	if (forced)
		line += "  (F)";

	unsigned long now = System::currentTimeSeconds();

	if (forced || line != last || lastTime + 3 < now)
	{
		last = line;
		lastTime = now;

		logger.debug() << line << std::endl;

		if (logger.isTraceEnabled())
		{
			{
				std::ostream &out = logger.trace();
				for (int i = 0; i < highest; i++)
					out << Convert::toString(i)[0];
				out << std::endl;
			}

			if (highest >= 10)
			{
				std::ostream &out = logger.trace();
				for (int i = 0; i < highest; i++)
					out << (i < 10 ? ' ' : Convert::toString(i)[1]);
				out << std::endl;
			}

			if (highest >= 100)
			{
				std::ostream &out = logger.trace();
				for (int i = 0; i < highest; i++)
					out << (i < 100 ? ' ' : Convert::toString(i)[2]);
				out << std::endl;
			}
		}
	}
}
