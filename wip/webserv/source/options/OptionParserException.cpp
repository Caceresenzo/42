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

#include <options/OptionParserException.hpp>

OptionParserException::OptionParserException() :
		Exception()
{
}

OptionParserException::OptionParserException(const std::string &message) :
		Exception(message)
{
}

OptionParserException::OptionParserException(const OptionParserException &other) :
		Exception(other)
{
}

OptionParserException::~OptionParserException() throw ()
{
}

OptionParserException&
OptionParserException::operator =(const OptionParserException &other)
{
	Exception::operator =(other);

	return (*this);
}
