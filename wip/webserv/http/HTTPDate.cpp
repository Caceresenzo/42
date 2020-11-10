/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPDate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:26:03 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 12:26:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/Exception.hpp>
#include <http/HTTPDate.hpp>
#include <sys/time.h>
#include <ctime>
#include <string>

HTTPDate::HTTPDate() :
		m_time()
{
}

HTTPDate::HTTPDate(time_t time) :
		m_time(time)
{
}

HTTPDate::HTTPDate(const HTTPDate &other) :
		m_time(other.m_time)
{
}

HTTPDate::~HTTPDate()
{
}

HTTPDate&
HTTPDate::operator =(const HTTPDate &other)
{
	if (this != &other)
		m_time = other.m_time;

	return (*this);
}

std::string
HTTPDate::format(void) const
{
	// max size = day-name, day month year hour:minute:second GMT
	//			= 3       1 2   3     4    2    2      2      3
	//			=          1   1     1    1    1      1      1
	//			== 29, but 35 (just in case)

	char str[35] = { 0 };
	::strftime(str, sizeof(str), HTTPDATE_FORMAT, &m_time);

	return (std::string(str));
}

HTTPDate::time_t
HTTPDate::time(void) const
{
	return (m_time);
}

HTTPDate
HTTPDate::now()
{
	HTTPDate date;

	struct timeval tv;
	struct tm *tm;

	::gettimeofday(&tv, NULL);
	if ((tm = ::localtime(&tv.tv_sec)))
		return (HTTPDate(*tm));

	throw Exception("localtime");
}
