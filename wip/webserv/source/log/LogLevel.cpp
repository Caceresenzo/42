/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 16:09:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <log/LogLevel.hpp>
#include <stddef.h>

#define DEFINE_LEVEL(name, color) ENUM_DEFINE(LogLevel, name, LogLevel(color));

DEFINE_LEVEL(TRACE, 94);
DEFINE_LEVEL(DEBUG, 96);
DEFINE_LEVEL(INFO, 92);
DEFINE_LEVEL(WARN, 93);
DEFINE_LEVEL(ERROR, 91);
DEFINE_LEVEL(FATAL, 31);

const LogLevel *LogLevel::ACTIVE = NULL;
bool LogLevel::COLORED = true;
std::ostream *LogLevel::OUTPUT = &std::cout;

LogLevel::LogLevel(int color) :
		m_color(color)
{
}

int
LogLevel::color() const
{
	return (m_color);
}
