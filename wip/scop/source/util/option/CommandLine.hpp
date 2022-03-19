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

class CommandLine
{
	public:
		typedef std::map<char, std::list<std::string> > map;
		typedef map::const_iterator iterator;

	private:
		map m_storage;

	public:
		CommandLine();
		CommandLine(map storage);
		CommandLine(const CommandLine &other);

		virtual
		~CommandLine();

		CommandLine&
		operator =(const CommandLine &other);

		bool
		has(const Option &option) const;

		bool
		has(char short_name) const;

		const std::list<std::string>&
		get(const Option &option) const;

		const std::list<std::string>&
		get(char short_name) const;

		const std::string&
		first(const Option &option) const;

		const std::string&
		first(char short_name) const;

		const std::string&
		last(const Option &option) const;

		const std::string&
		last(char short_name) const;

		iterator
		find(const Option &option) const;

		iterator
		find(char short_name) const;
};

#endif /* COMMANDLINE_HPP_ */
