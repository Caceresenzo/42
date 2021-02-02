/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:07:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 16:07:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <log/Logger.hpp>

Logger::~Logger()
{
}

bool
Logger::isTraceEnabled() const
{
	return (isEnabled(*LogLevel::TRACE));
}

bool
Logger::isDebugEnabled() const
{
	return (isEnabled(*LogLevel::DEBUG));
}

bool
Logger::isInfoEnabled() const
{
	return (isEnabled(*LogLevel::INFO));
}

bool
Logger::isWarnEnabled() const
{
	return (isEnabled(*LogLevel::WARN));
}

bool
Logger::isErrorEnabled() const
{
	return (isEnabled(*LogLevel::ERROR));
}

bool
Logger::isFatalEnabled() const
{
	return (isEnabled(*LogLevel::FATAL));
}
