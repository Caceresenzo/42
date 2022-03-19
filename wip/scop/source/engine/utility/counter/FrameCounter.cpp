/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameCounter.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:57:17 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 23:57:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/utility/counter/FrameCounter.hpp>
#include <sys/time.h>
#include <cstdio>
#include <ctime>
#include <iostream>

FrameCounter::FrameCounter() :
		m_frame(0),
		m_last_time(0),
		m_last_per_seconds(0)
{
}

FrameCounter::FrameCounter(const FrameCounter &other) :
		m_frame(other.m_frame),
		m_last_time(other.m_last_time),
		m_last_per_seconds(other.m_last_per_seconds)
{
}

FrameCounter::~FrameCounter()
{
}

FrameCounter&
FrameCounter::operator=(const FrameCounter &other)
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
FrameCounter::count()
{
	int now = time(NULL);

	if (m_last_time != now)
	{
		if (m_last_time != 0)
		{
			long long took = now - m_last_time;
			float average = float(took) / float(m_frame);

			m_last_per_seconds = m_frame;

			std::cout << m_frame << " frame(s) in " << took << " s (or ~" << average << "s/frame)" << std::endl << std::flush;
		}

		m_frame = 0;
		m_last_time = now;
	}

	m_frame++;
}

int
FrameCounter::frame() const
{
	return (m_last_per_seconds);
}
