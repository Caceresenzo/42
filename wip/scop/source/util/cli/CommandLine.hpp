/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:39:58 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/15 19:39:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDLINE_HPP_
# define COMMANDLINE_HPP_

#include <list>
#include <map>
#include <string>

class Option;
class Argument;

class CommandLine
{
	public:
		typedef std::map<char, std::list<std::string> > option_map;
		typedef option_map::const_iterator option_iterator;
		typedef std::map<std::string, std::list<std::string> > argument_map;
		typedef argument_map::const_iterator argument_iterator;

	private:
		option_map m_options;
		argument_map m_arguments;

	public:
		CommandLine();
		CommandLine(option_map options, argument_map arguments);
		CommandLine(const CommandLine &other);

		virtual
		~CommandLine();

		CommandLine&
		operator=(const CommandLine &other);

		bool
		has(const Option &option) const;

		const std::list<std::string>&
		get(const Option &option) const;

		const std::string&
		first(const Option &option) const;

		option_iterator
		find(const Option &option) const;

		bool
		has(const Argument &argument) const;

		const std::list<std::string>&
		get(const Argument &argument) const;

		const std::string&
		first(const Argument &argument) const;

		argument_iterator
		find(const Argument &argument) const;
};

#endif /* COMMANDLINE_HPP_ */
