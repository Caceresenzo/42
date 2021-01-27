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

#include <options/OptionParser.hpp>
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
OptionParser::parse(int argc, char **argv) throw (OptionParserException)
{
	CommandLine::map values;

	for (int index = 1; index < argc; index++)
	{
		bool hasMore = (index + 1) < argc;

		char *current = argv[index];
		char *next = argv[index + 1]; /* NULL if hasMore == false. */

		if (current[0] == '-')
		{
			bool isLong = current[1] == '-';
			size_t startAt = 1 + isLong;

			std::string name = current + startAt;

			if (name.empty())
				throw OptionParserException(std::string("unparsable option: ") + current);

			bool consideredAsLong = isLong || name.length() > 1;

			const Option *found = NULL;
			for (iterator it = m_options.begin(); it != m_options.end(); it++)
			{
				const Option *option = *it;

				if (consideredAsLong && option->longName() == name)
				{
					found = option;
					break;
				}

				if (!consideredAsLong && name.at(0) == option->shortName())
				{
					found = option;
					break;
				}
			}

			if (!found)
				throw OptionParserException(std::string("unrecognized option: '") + current + std::string("'"));

			const char *argument = "";
			if (found->hasArgument())
			{
				index++;

				if (!hasMore)
					throw OptionParserException(std::string("option requires an argument: '") + current + std::string(" <") + found->argumentName() + std::string(">'"));

				argument = next;
			}

			values[found->shortName()].push_back(argument);
		}
		else
			throw OptionParserException(std::string("unrecognized input: '") + current + std::string("'"));
	}

	return (CommandLine(values));
}

std::string
OptionParser::help(const std::string &program, const std::string &description, const std::vector<std::string> &authors) const
{
	size_t longestLong = 0;

	for (iterator it = m_options.begin(); it != m_options.end(); it++)
		longestLong = std::max(longestLong, (*it)->longName().size() + (*it)->argumentName().size() + 3);

	std::stringstream stream;
	stream << "Usage: " << program << " [OPTION]..." << std::endl;
	stream << description << std::endl << std::endl;

	for (iterator it = m_options.begin(); it != m_options.end(); it++)
	{
		const Option *option = *it;

		stream << "  -" << option->shortName();
		stream << ", --" << std::setw(longestLong) << std::left;

		if (option->hasArgument())
			stream << option->longName() + (" <" + option->argumentName() + ">");
		else
			stream << option->longName();

		stream << "  " << option->description();
		stream << std::endl;
	}

	stream << std::endl;

	if (!authors.empty())
	{
		stream << "Authors:" << std::endl;

		for (std::vector<std::string>::const_iterator it = authors.begin(); it != authors.end(); it++)
			stream << "  " << *it << std::endl;
	}

	return (stream.str());
}
