/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HighFrameCounter.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:57:17 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 23:57:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/utility/counter/HighFrameCounter.hpp>
#include <sys/_timeval.h>
#include <sys/time.h>
#include <cstdio>
#include <ctime>
#include <iostream>

HighFrameCounter::HighFrameCounter() :
		m_frame(0),
		m_last_time(0),
		m_last_per_seconds(0)
{
}

HighFrameCounter::HighFrameCounter(const HighFrameCounter &other) :
		m_frame(other.m_frame),
		m_last_time(other.m_last_time),
		m_last_per_seconds(other.m_last_per_seconds)
{
}

HighFrameCounter::~HighFrameCounter()
{
}

HighFrameCounter&
HighFrameCounter::operator=(const HighFrameCounter &other)
{
	if (this != &other)
	{
		m_frame = other.m_frame;
		m_last_time = other.m_last_time;
		m_last_per_seconds = other.m_last_per_seconds;
	}

	return (*this);
}

void
HighFrameCounter::count()
{
	struct timeval te;
	gettimeofday(&te, NULL);
	long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;

	if (m_last_time != milliseconds)
	{
		if (m_last_time != 0)
		{
			long long took = milliseconds - m_last_time;
			float average = float(took) / float(m_frame);

			m_last_per_seconds = 1000 / average;
		}

		m_frame = 0;
		m_last_time = milliseconds;
	}

	m_frame++;
}

int
HighFrameCounter::frame() const
{
	return (m_last_per_seconds);
}
