/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <cstring>

#include "Logger.hpp"

#define ENSURE_DOUBLE_DIGIT(number) ((number < 10) ? "0" : "") << number

Logger::Logger(std::string file)
{
	this->_stream.open(file.c_str(), std::ofstream::out | std::ofstream::app);

	if (!this->_stream.is_open())
		this->log(DEST_CONSOLE, "WARNING: Failed to open output log file \"" + file + "\": " + strerror(errno));
	else
		this->_stream << std::endl;
}

Logger::~Logger(void)
{
	if (this->_stream.is_open())
		this->_stream.close();
}

std::string
Logger::makeLogEntry(std::string const &msg)
{
	std::stringstream stream;

    time_t t = time(0);
    tm* now = localtime(&t);

    stream
		<< "["
		<< (now->tm_year + 1900)
		<< "/"
        << ENSURE_DOUBLE_DIGIT((now->tm_mon + 1))
		<< "/"
        << ENSURE_DOUBLE_DIGIT(now->tm_mday)
		<< " "
        << ENSURE_DOUBLE_DIGIT(now->tm_hour)
		<< ":"
        << ENSURE_DOUBLE_DIGIT(now->tm_min)
		<< ":"
        << ENSURE_DOUBLE_DIGIT(now->tm_sec)
        << "] "
        << msg;

    return (stream.str());
}

void
Logger::logToConsole(std::string const &msg)
{
	std::cout << msg << std::endl;
}

void
Logger::logToFile(std::string const &msg)
{
	if (this->_stream.is_open())
		this->_stream << msg << std::endl;
}

void
Logger::log(std::string const &dest, std::string const &message)
{
	void (Logger::*methods[])(std::string const &) = {
		&Logger::logToConsole,
		&Logger::logToFile
	};
	std::string names[] = {
		DEST_CONSOLE,
		DEST_FILE
	};

	for (size_t index = 0; index < (sizeof(names) / sizeof(std::string)); index++)
	{
		void (Logger::*method)(std::string const &) = methods[index];
		std::string name = names[index];

		if (name == dest)
		{
			(this->*method)(makeLogEntry(message));

			break ;
		}
	}
}
