/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericToken.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumericToken.hpp"

#include <sstream>

NumericToken::NumericToken() :
        Token(),
        _value(0)
{
}

NumericToken::NumericToken(int value) :
        Token(),
        _value(value)
{
}

NumericToken::NumericToken(const NumericToken &other) :
        Token(other),
        _value(other._value)
{
	this->operator =(other);
}

NumericToken::~NumericToken()
{
}

NumericToken&
NumericToken::operator=(const NumericToken &other)
{
	Token::operator =(other);

	if (this != &other)
	{
		this->_value = other._value;
	}

	return (*this);
}

int
NumericToken::value() const
{
	return _value;
}

Token*
NumericToken::clone() const
{
	return (new NumericToken(*this));
}

std::string
NumericToken::toString() const
{
	std::stringstream stream;

	stream << "Num(" << value() << ")";

	return (stream.str());
}
