/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLineParserException.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/16 13:30:44 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDLINEPARSEREXCEPTION_HPP_
# define COMMANDLINEPARSEREXCEPTION_HPP_

#include <lang/Exception.hpp>
#include <string>

class CommandLineParserException :
		public Exception
{
	public:
		CommandLineParserException(void);
		CommandLineParserException(const std::string &message);
		CommandLineParserException(const CommandLineParserException &other);

		virtual
		~CommandLineParserException() throw ();

		CommandLineParserException&
		operator=(const CommandLineParserException &other);
};

#endif /* PARSEREXCEPTION_HPP_ */
