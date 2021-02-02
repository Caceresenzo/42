/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerImpl.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:54:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/20 10:54:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <log/LoggerImpl.hpp>
#include <log/LogLevel.hpp>
#include <stddef.h>
#include <util/Convert.hpp>
#include <util/Enum.hpp>
#include <algorithm>
#include <iomanip>

size_t LoggerImpl::LONGEST_NAME = 0;
const std::string LoggerImpl::DEFAULT_TAG = "???";
NullStream LoggerImpl::VOID;

LoggerImpl::LoggerImpl() :
		m_tag(DEFAULT_TAG)
{
}

LoggerImpl::LoggerImpl(const std::string &tag) :
		m_tag(tag)
{
	LoggerImpl::LONGEST_NAME = std::max(LoggerImpl::LONGEST_NAME, tag.size());
}

LoggerImpl::LoggerImpl(const LoggerImpl &other) :
		m_tag(other.m_tag)
{
}

LoggerImpl::~LoggerImpl()
{
}

std::ostream&
LoggerImpl::trace() const
{
	return (log(*LogLevel::TRACE));
}

std::ostream&
LoggerImpl::debug() const
{
	return (log(*LogLevel::DEBUG));
}

std::ostream&
LoggerImpl::info() const
{
	return (log(*LogLevel::INFO));
}

std::ostream&
LoggerImpl::warn() const
{
	return (log(*LogLevel::WARN));
}

std::ostream&
LoggerImpl::error() const
{
	return (log(*LogLevel::ERROR));
}

std::ostream&
LoggerImpl::fatal() const
{
	return (log(*LogLevel::FATAL));
}

std::ostream&
LoggerImpl::log(const LogLevel &level) const
{
	if (!isEnabled(level))
		return (VOID);

	static std::string colorIn = "\e[";
	static std::string colorOut = "\e[0m";

	*LogLevel::OUTPUT << '[';

	if (LogLevel::COLORED)
		*LogLevel::OUTPUT << colorIn + Convert::toString(level.color()) + 'm';

	*LogLevel::OUTPUT << std::setw(5) << level.name() << std::setw(0);

	if (LogLevel::COLORED)
		*LogLevel::OUTPUT << colorOut;

	return (*LogLevel::OUTPUT << ']' << std::setw(LONGEST_NAME) << m_tag << ": ");
}

const std::string&
LoggerImpl::tag() const
{
	return (m_tag);
}

bool
LoggerImpl::isEnabled(const LogLevel &level) const
{
	return (!(LogLevel::ACTIVE == NULL || LogLevel::ACTIVE->ordinal() > level.ordinal()));
}
