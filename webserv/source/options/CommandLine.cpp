/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:39:58 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/15 19:39:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <options/CommandLine.hpp>
#include <options/Option.hpp>

CommandLine::CommandLine() :
		m_storage()
{
}

CommandLine::CommandLine(map storage) :
		m_storage(storage)
{
}

CommandLine::CommandLine(const CommandLine &other) :
		m_storage(other.m_storage)
{
}

CommandLine::~CommandLine()
{
}

CommandLine&
CommandLine::operator =(const CommandLine &other)
{
	if (this != &other)
		m_storage = other.m_storage;

	return (*this);
}

bool
CommandLine::has(const Option &option) const
{
	return (has(option.shortName()));
}

bool
CommandLine::has(char shortName) const
{
	return (find(shortName) != m_storage.end());
}

const std::list<std::string>&
CommandLine::get(const Option &option) const
{
	return (get(option.shortName()));
}

const std::list<std::string>&
CommandLine::get(char shortName) const
{
	return (find(shortName)->second);
}

const std::string&
CommandLine::first(const Option &option) const
{
	return (first(option.shortName()));
}

const std::string&
CommandLine::first(char shortName) const
{
	return (get(shortName).front());
}

const std::string&
CommandLine::last(const Option &option) const
{
	return (last(option.shortName()));
}

const std::string&
CommandLine::last(char shortName) const
{
	return (get(shortName).back());
}

CommandLine::iterator
CommandLine::find(const Option &option) const
{
	return (find(option.shortName()));
}

CommandLine::iterator
CommandLine::find(char shortName) const
{
	return (m_storage.find(shortName));
}
