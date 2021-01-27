/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptorSet.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:51:36 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 23:51:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/FileDescriptorSet.hpp>

const int FileDescriptorSet::MAX = FD_SETSIZE;

FileDescriptorSet::FileDescriptorSet() :
		m_storage(),
		m_size()
{
	zero();
}

FileDescriptorSet::FileDescriptorSet(const FileDescriptorSet &other) :
		m_storage(other.m_storage),
		m_size(other.m_size)
{
}

FileDescriptorSet::~FileDescriptorSet()
{
}

FileDescriptorSet&
FileDescriptorSet::operator =(const FileDescriptorSet &other)
{
	if (this != &other)
	{
		m_storage = other.m_storage;
		m_size = other.m_size;
	}

	return (*this);
}

void
FileDescriptorSet::zero()
{
	FD_ZERO(&m_storage);
	m_size = 0;
}

void
FileDescriptorSet::set(int n)
{
	if (!FD_ISSET(n, &m_storage))
	{
		FD_SET(n, &m_storage);
		m_size++;
	}
}

void
FileDescriptorSet::clear(int n)
{
	if (FD_ISSET(n, &m_storage))
	{
		FD_CLR(n, &m_storage);
		m_size--;
	}
}

bool
FileDescriptorSet::test(int n) const
{
	return (FD_ISSET(n, &m_storage));
}

int
FileDescriptorSet::size() const
{
	return (m_size);
}

bool
FileDescriptorSet::empty() const
{
	return (m_size == 0);
}

fd_set&
FileDescriptorSet::storage()
{
	return (m_storage);
}

