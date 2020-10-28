/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:54:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/20 10:54:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/Logger.hpp>

const std::string Logger::DEFAULT_TAG = "???";
std::map<std::string, Logger*> Logger::INSTANCES = std::map<std::string, Logger*>();

Logger::Logger() :
		m_tag(DEFAULT_TAG)
{
}

Logger::Logger(const std::string &tag) :
		m_tag(tag)
{
}

Logger::Logger(const Logger &other) :
		m_tag(other.m_tag)
{
}

Logger::~Logger()
{
}

std::ostream&
Logger::trace() const
{
	return (log(LL_TRACE));
}

std::ostream&
Logger::debug() const
{
	return (log(LL_DEBUG));
}

std::ostream&
Logger::info() const
{
	return (log(LL_INFO));
}

std::ostream&
Logger::warn() const
{
	return (log(LL_WARN));
}

std::ostream&
Logger::error() const
{
	return (log(LL_ERROR));
}

std::ostream&
Logger::fatal() const
{
	return (log(LL_FATAL));
}

std::ostream&
Logger::log(Level level) const
{
	return (std::cout << "[" << levelToString(level) << "] " << m_tag << ": ");
}

const std::string&
Logger::tag() const
{
	return (m_tag);
}

Logger&
Logger::factory(const std::string &tag)
{
	Logger *current = INSTANCES[tag];

	if (!current)
	{
		current = new Logger(tag);

		INSTANCES.insert(INSTANCES.end(), std::pair<std::string, Logger*>(tag, current));
	}

	return (*current);
}

std::string
Logger::levelToString(Level level)
{
	static std::string strings[_LL_SIZE] = { "TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "FATAL", };

	return (strings[level]);
}

void
Logger::deleteAll(void)
{
}
