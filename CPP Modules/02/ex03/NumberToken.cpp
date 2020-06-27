/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumberToken.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:51:54 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 14:51:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumberToken.hpp"

#include <sstream>
#include <string>

NumberToken::NumberToken() :
		Token(TT_NUMBER), _value(Fixed(0))
{
}

NumberToken::NumberToken(const Fixed fixed) :
		Token(TT_NUMBER), _value(fixed)
{
}

NumberToken::NumberToken(const NumberToken &other) :
		Token(other)
{
	this->operator =(other);
}

NumberToken::~NumberToken()
{
}

NumberToken&
NumberToken::operator=(const NumberToken &other)
{
	if (this != &other)
	{
		Token::operator =(other);

		this->_value = other._value;
	}

	return (*this);
}

const Fixed
NumberToken::getValue(void) const
{
	return (this->_value);
}

std::string const
NumberToken::toString(void) const
{
	std::stringstream ss;
	ss << _value;

	return ("NumberToken[type=" + Token::typeName(this->type()) + ", value=" + ss.str() + "]");
}
