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

#include <util/option/CommandLine.hpp>
#include <util/option/Option.hpp>

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
	return (has(option.short_name()));
}

bool
CommandLine::has(char short_name) const
{
	return (find(short_name) != m_storage.end());
}

const std::list<std::string>&
CommandLine::get(const Option &option) const
{
	return (get(option.short_name()));
}

const std::list<std::string>&
CommandLine::get(char short_name) const
{
	return (find(short_name)->second);
}

const std::string&
CommandLine::first(const Option &option) const
{
	return (first(option.short_name()));
}

const std::string&
CommandLine::first(char short_name) const
{
	return (get(short_name).front());
}

const std::string&
CommandLine::last(const Option &option) const
{
	return (last(option.short_name()));
}

const std::string&
CommandLine::last(char short_name) const
{
	return (get(short_name).back());
}

CommandLine::iterator
CommandLine::find(const Option &option) const
{
	return (find(option.short_name()));
}

CommandLine::iterator
CommandLine::find(char short_name) const
{
	return (m_storage.find(short_name));
}
