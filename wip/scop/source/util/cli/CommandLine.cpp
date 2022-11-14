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

#include <util/cli/Argument.hpp>
#include <util/cli/CommandLine.hpp>
#include <util/cli/Option.hpp>

CommandLine::CommandLine() :
	m_options(),
	m_arguments()
{
}

CommandLine::CommandLine(option_map options, argument_map arguments) :
	m_options(options),
	m_arguments(arguments)
{
}

CommandLine::CommandLine(const CommandLine &other) :
	m_options(other.m_options),
	m_arguments(other.m_arguments)
{
}

CommandLine::~CommandLine()
{
}

CommandLine&
CommandLine::operator=(const CommandLine &other)
{
	if (this != &other)
	{
		m_options = other.m_options;
		m_arguments = other.m_arguments;
	}

	return (*this);
}

bool
CommandLine::has(const Option &option) const
{
	return (find(option) != m_options.end());
}

const std::list<std::string>&
CommandLine::get(const Option &option) const
{
	return (find(option)->second);
}

const std::string&
CommandLine::first(const Option &option) const
{
	return (get(option).front());
}

CommandLine::option_iterator
CommandLine::find(const Option &option) const
{
	return (m_options.find(option.short_name()));
}

bool
CommandLine::has(const Argument &option) const
{
	return (find(option) != m_arguments.end());
}

const std::list<std::string>&
CommandLine::get(const Argument &option) const
{
	return (find(option)->second);
}

const std::string&
CommandLine::first(const Argument &option) const
{
	return (get(option).front());
}

CommandLine::argument_iterator
CommandLine::find(const Argument &option) const
{
	return (m_arguments.find(option.name()));
}

