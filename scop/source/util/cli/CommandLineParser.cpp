/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:36:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/17 09:38:57 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <util/cli/CommandLineParser.hpp>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>

CommandLineParser::CommandLineParser(option_list options) :
	m_options(options),
	m_arguments()
{
}

CommandLineParser::CommandLineParser(option_list options, argument_list arguments) :
	m_options(options),
	m_arguments(arguments)
{
}

CommandLineParser::~CommandLineParser(void)
{
}

CommandLine
CommandLineParser::parse(int argc, char **argv)
{
	CommandLine::option_map option_values;
	CommandLine::argument_map argument_values;

	for (int index = 1; index < argc; index++)
	{
		bool has_more = (index + 1) < argc;

		char *current = argv[index];
		char *next = argv[index + 1]; /* NULL if hasMore == false. */

		if (current[0] == '-')
		{
			bool is_long = current[1] == '-';
			size_t start_at = 1 + is_long;

			std::string name = current + start_at;

			if (name.empty())
				throw CommandLineParserException(std::string("unparsable option: ") + current);

			bool considered_as_long = is_long || name.length() > 1;

			const Option *found = NULL;
			for (option_iterator it = m_options.begin(); it != m_options.end(); it++)
			{
				const Option *option = *it;

				if (considered_as_long && option->long_name() == name)
				{
					found = option;
					break;
				}

				if (!considered_as_long && option->short_name() != 0 && name.at(0) == option->short_name())
				{
					found = option;
					break;
				}
			}

			if (!found)
				throw CommandLineParserException(std::string("unrecognized option: '") + current + std::string("'"));

			const char *argument = "";
			if (found->has_argument())
			{
				index++;

				if (!has_more)
					throw CommandLineParserException(std::string("option requires an argument: '") + current + std::string(" <") + found->argument_name() + std::string(">'"));

				argument = next;
			}

			option_values[found->short_name()].push_back(argument);
		}
		else
		{
			argument_iterator it = m_arguments.begin() + argument_values.size();
			if (it >= m_arguments.end())
				throw CommandLineParserException(std::string("unrecognized input: '") + current + std::string("'"));

			argument_values[(*it)->name()].push_back(current);
		}
	}

	return (CommandLine(option_values, argument_values));
}

std::string
CommandLineParser::help(const std::string &program, const std::string &description, const std::vector<std::string> &authors) const
{
	std::stringstream stream;
	stream << "Usage: " << program << " [OPTIONS...] [ARGUMENTS...]" << std::endl;
	stream << description << std::endl << std::endl;

	size_t longest_long = 0;
	for (option_iterator it = m_options.begin(); it != m_options.end(); it++)
		longest_long = std::max(longest_long, (*it)->long_name().size() + (*it)->argument_name().size());
	for (argument_iterator it = m_arguments.begin(); it != m_arguments.end(); it++)
		longest_long = std::max(longest_long, (*it)->name().size());
	longest_long += 3;

	if (!m_options.empty())
	{
		stream << "option";
		if (m_options.size() != 1)
			stream << "s";
		stream << ":" << std::endl;

		for (option_iterator it = m_options.begin(); it != m_options.end(); it++)
		{
			const Option *option = *it;

			if (option->short_name())
				stream << "  -" << option->short_name() << ',';
			else
				stream << "     ";

			stream << " --" << std::setw(longest_long) << std::left;

			if (option->has_argument())
				stream << option->long_name() + (" <" + option->argument_name() + ">");
			else
				stream << option->long_name();

			stream << "  " << option->description();
			stream << std::endl;
		}

		stream << std::endl;
	}

	if (!m_arguments.empty())
	{
		stream << "argument";
		if (m_arguments.size() != 1)
			stream << "s";
		stream << ":" << std::endl;

		for (argument_iterator it = m_arguments.begin(); it != m_arguments.end(); it++)
		{
			const Argument *argument = *it;

			stream << "  " << std::setw(longest_long + 6) << std::left;
			stream << argument->format_name();

			stream << "  " << argument->description();
			stream << std::endl;
		}

		stream << std::endl;
	}

	if (!authors.empty())
	{
		stream << "author";
		if (authors.size() != 1)
			stream << "s";
		stream << ":" << std::endl;

		for (std::vector<std::string>::const_iterator it = authors.begin(); it != authors.end(); it++)
			stream << "  " << *it << std::endl;
	}

	return (stream.str());
}
