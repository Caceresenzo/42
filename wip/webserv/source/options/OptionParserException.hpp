/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParserException.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/16 13:30:44 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONPARSEREXCEPTION_HPP_
# define OPTIONPARSEREXCEPTION_HPP_

#include <exception/Exception.hpp>
#include <string>

class OptionParserException :
		public Exception
{
	public:
		OptionParserException(void);
		OptionParserException(const std::string &message);
		OptionParserException(const OptionParserException &other);

		virtual
		~OptionParserException() throw ();

		OptionParserException&
		operator=(const OptionParserException &other);
};

#endif /* PARSEREXCEPTION_HPP_ */
