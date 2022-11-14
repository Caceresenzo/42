/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParserException.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/17 09:41:28 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/cli/CommandLineParserException.hpp>

CommandLineParserException::CommandLineParserException() :
		Exception()
{
}

CommandLineParserException::CommandLineParserException(const std::string &message) :
		Exception(message)
{
}

CommandLineParserException::CommandLineParserException(const CommandLineParserException &other) :
		Exception(other)
{
}

CommandLineParserException::~CommandLineParserException() throw ()
{
}

CommandLineParserException&
CommandLineParserException::operator =(const CommandLineParserException &other)
{
	Exception::operator =(other);

	return (*this);
}
