/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:03:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 23:03:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IOException.hpp>
#include <libs/ft.hpp>
#include <sys/errno.h>
#include <sys/time.h>
#include <util/Time.hpp>
#include <string>

Time::Time() :
		m_time()
{
}

Time::Time(long seconds) :
		m_time(fromLong(seconds))
{
}

Time::Time(timespec_t timespec) :
		m_time(fromLong(timespec.tv_sec))
{
}
Time::Time(timeval_t timeval) :
		m_time(fromLong(timeval.tv_sec))
{
}

Time::Time(time_t time) :
		m_time(time)
{
}

Time::Time(const Time &other) :
		m_time(other.m_time)
{
}

Time::~Time()
{
}

Time&
Time::operator=(const Time &other)
{
	if (this != &other)
		m_time = other.m_time;

	return (*this);
}

size_t
Time::cformat(char *str, size_t maxSize, const char *format) const
{
	return (::strftime(str, maxSize, format, &m_time));
}

std::string
Time::cformat(const char *format) const
{
	size_t len = ft::strlen(format) * 3;
	char str[len];
	ft::bzero(str, len);

	size_t r = cformat(str, len, format);

	return (std::string(str, r));
}

Time::time_t
Time::fromLong(long seconds)
{
	time_t *time;

	if ((time = ::localtime(&seconds)))
		return (*time);

	throw IOException("localtime", errno);
}

Time
Time::now()
{
	timeval_t timeval;
	if (::gettimeofday(&timeval, NULL) == -1)
		throw IOException("gettimeofday", errno);

	return (Time(timeval));
}
