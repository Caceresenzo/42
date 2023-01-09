/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLineParser.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:36:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/16 17:06:25 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDLINEPARSER_HPP_
# define COMMANDLINEPARSER_HPP_

#include <util/cli/Argument.hpp>
#include <util/cli/CommandLine.hpp>
#include <util/cli/CommandLineParserException.hpp>
#include <util/cli/Option.hpp>
#include <list>
#include <string>
#include <vector>

class CommandLine;

class CommandLineParser
{
	public:
		typedef std::vector<const Option*> option_list;
		typedef std::vector<const Argument*> argument_list;
		typedef option_list::const_iterator option_iterator;
		typedef argument_list::const_iterator argument_iterator;

	private:
		option_list m_options;
		argument_list m_arguments;

	public:
		CommandLineParser(option_list options);
		CommandLineParser(option_list options, argument_list arguments);

		virtual
		~CommandLineParser(void);

		CommandLine
		parse(int argc, char **argv);

		std::string
		help(const std::string &program, const std::string &description, const std::vector<std::string> &authors) const;
};

#endif /* COMMANDLINEPARSER_HPP_ */
