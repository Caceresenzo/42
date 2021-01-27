/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:03:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 23:03:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_HPP_
# define TIME_HPP_

#include <stddef.h>
#include <string>

struct timespec;
struct timeval;
struct tm;

#if 1
#include <ctime>
#endif

class Time
{
	public:
		typedef struct tm time_t;
		typedef struct timespec timespec_t;
		typedef struct timeval timeval_t;

	private:
		time_t m_time;

	public:
		Time();
		Time(long seconds);
		Time(timeval_t timespec);
		Time(timespec_t timeval);
		Time(time_t time);
		Time(const Time &other);

		virtual
		~Time();

		Time&
		operator=(const Time &other);

		size_t
		cformat(char *str, size_t maxSize, const char *format) const;

		std::string
		cformat(const char *format) const;

	private:
		static time_t
		fromLong(long seconds);

	public:
		static Time
		now();

};

#endif /* TIME_HPP_ */
