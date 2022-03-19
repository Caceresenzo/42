/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:36:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/16 17:06:25 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONPARSER_HPP_
# define OPTIONPARSER_HPP_

#include <util/option/Option.hpp>
#include <util/option/CommandLine.hpp>
#include <util/option/OptionParserException.hpp>
#include <vector>
#include <list>

class OptionParser
{
	public:
		typedef std::list<const Option*> list;
		typedef list::const_iterator iterator;

	private:
		list m_options;

	private:
		OptionParser();
		OptionParser(const OptionParser &other);

		OptionParser&
		operator=(const OptionParser &other);

	public:
		OptionParser(list options);

		virtual
		~OptionParser(void);

		CommandLine
		parse(int argc, char **argv);

		std::string
		help(const std::string &program, const std::string &description, const std::vector<std::string> &authors) const;
};

#endif /* OPTIONPARSER_HPP_ */
