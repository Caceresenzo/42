/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPVersion.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:43:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/26 15:09:47 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPVersion.hpp>
#include <sstream>

# ifdef _SYS_SYSMACROS_H
#  undef major
#  undef minor
# endif

HTTPVersion HTTPVersion::HTTP_1_1 = HTTPVersion(1, 1);

HTTPVersion::HTTPVersion(void) :
		m_major(0),
		m_minor(0)
{
}

HTTPVersion::HTTPVersion(int major, int minor) :
		m_major(major),
		m_minor(minor)
{
}

HTTPVersion::HTTPVersion(const HTTPVersion &other) :
		m_major(other.m_major),
		m_minor(other.m_minor)
{
}

HTTPVersion::~HTTPVersion(void)
{
}

HTTPVersion&
HTTPVersion::operator=(const HTTPVersion &other)
{
	if (this != &other)
	{
		m_major = other.m_major;
		m_minor = other.m_minor;
	}

	return (*this);
}

int
HTTPVersion::major(void) const
{
	return (m_major);
}

int
HTTPVersion::minor(void) const
{
	return (m_minor);
}

std::string
HTTPVersion::format(void) const
{
	std::stringstream stream;

	stream << "HTTP/" << m_major << "." << m_minor;

	return (stream.str());
}

bool
HTTPVersion::isSupported(int major, int minor)
{
	return (major == 1 && minor == 1);
}
