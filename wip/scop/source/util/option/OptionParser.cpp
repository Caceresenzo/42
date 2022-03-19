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

#include <util/option/OptionParser.hpp>
#include <stddef.h>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>

OptionParser::OptionParser(list options) :
		m_options(options)
{
}

OptionParser::~OptionParser(void)
{
}

CommandLine
OptionParser::parse(int argc, char **argv)
{
	CommandLine::map values;

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
				throw OptionParserException(std::string("unparsable option: ") + current);

			bool considered_as_long = is_long || name.length() > 1;

			const Option *found = NULL;
			for (iterator it = m_options.begin(); it != m_options.end(); it++)
			{
				const Option *option = *it;

				if (considered_as_long && option->long_name() == name)
				{
					found = option;
					break;
				}

				if (!considered_as_long && name.at(0) == option->short_name())
				{
					found = option;
					break;
				}
			}

			if (!found)
				throw OptionParserException(std::string("unrecognized option: '") + current + std::string("'"));

			const char *argument = "";
			if (found->has_argument())
			{
				index++;

				if (!has_more)
					throw OptionParserException(std::string("option requires an argument: '") + current + std::string(" <") + found->argument_name() + std::string(">'"));

				argument = next;
			}

			values[found->short_name()].push_back(argument);
		}
		else
			throw OptionParserException(std::string("unrecognized input: '") + current + std::string("'"));
	}

	return (CommandLine(values));
}

std::string
OptionParser::help(const std::string &program, const std::string &description, const std::vector<std::string> &authors) const
{
	size_t longest_long = 0;

	for (iterator it = m_options.begin(); it != m_options.end(); it++)
		longest_long = std::max(longest_long, (*it)->long_name().size() + (*it)->argument_name().size() + 3);

	std::stringstream stream;
	stream << "Usage: " << program << " [OPTION]..." << std::endl;
	stream << description << std::endl << std::endl;

	for (iterator it = m_options.begin(); it != m_options.end(); it++)
	{
		const Option *option = *it;

		stream << "  -" << option->short_name();
		stream << ", --" << std::setw(longest_long) << std::left;

		if (option->has_argument())
			stream << option->long_name() + (" <" + option->argument_name() + ">");
		else
			stream << option->long_name();

		stream << "  " << option->description();
		stream << std::endl;
	}

	stream << std::endl;

	if (!authors.empty())
	{
		stream << "Author";
		if (authors.size() != 1)
			stream << "s";
		stream << ":" << std::endl;

		for (std::vector<std::string>::const_iterator it = authors.begin(); it != authors.end(); it++)
			stream << "  " << *it << std::endl;
	}

	return (stream.str());
}
