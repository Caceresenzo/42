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
#include <lang/System.hpp>
#include <cstdio>
#include <ctime>
#include <iostream>

HighFrameCounter::HighFrameCounter() :
		m_frame(0),
		m_last_time(0),
		m_last_per_seconds(0),
		m_last(0),
		m_current(0)
{
}

HighFrameCounter::HighFrameCounter(const HighFrameCounter &other) :
		m_frame(other.m_frame),
		m_last_time(other.m_last_time),
		m_last_per_seconds(other.m_last_per_seconds),
		m_last(0),
		m_current(0)
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
HighFrameCounter::reset()
{
	m_current = 0;
	m_last = System::current_time_millis();
}

void
HighFrameCounter::start()
{
	m_current = System::current_time_millis();
}

void
HighFrameCounter::end()
{
	m_last = m_current;
}

double
HighFrameCounter::delta_time() const
{
	return (double(m_current - m_last) / 1000.0);
}

void
HighFrameCounter::count()
{
	long long milliseconds = System::current_time_millis();

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
