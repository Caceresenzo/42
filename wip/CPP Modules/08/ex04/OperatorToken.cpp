/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorToken.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperatorToken.hpp"

#include <exception>
#include <sstream>
#include <string>

OperatorToken::OperatorToken() :
        Token(),
        _type(OP_ADD)
{
}

OperatorToken::OperatorToken(OperatorType type) :
        Token(),
        _type(type)
{
}

OperatorToken::OperatorToken(const OperatorToken &other) :
        Token(other),
        _type(other._type)
{
	this->operator =(other);
}

OperatorToken::~OperatorToken()
{
}

OperatorToken&
OperatorToken::operator=(const OperatorToken &other)
{
	Token::operator =(other);

	if (this != &other)
	{
		this->_type = other._type;
	}

	return (*this);
}

int
OperatorToken::use(int left, int right)
{
	switch (_type)
	{
		case OP_ADD:
			return (left + right);

		case OP_SUBSTRACT:
			return (left - right);

		case OP_MULTIPLY:
			return (left * right);

		case OP_DEVIDE:
			{
			if (right == 0)
				throw OperatorToken::ArithmeticException(std::string("/ by zero"));

			return (left / right);
		}

		case OP__LENGTH:
			break;
	}

	throw std::exception();
}

OperatorType
OperatorToken::type() const
{
	return (_type);
}

char
OperatorToken::toChar() const
{
	static const char operatorToChar[OP__LENGTH] = {
	        '+', '-', '*', '/'
	};

	return (operatorToChar[type()]);
}

std::string
OperatorToken::english() const
{
	static const std::string operatorToString[OP__LENGTH] = {
	        "Add",
	        "Substract",
	        "Multiply",
	        "Devide"
	};

	return (operatorToString[type()]);
}

Token*
OperatorToken::clone() const
{
	return (new OperatorToken(*this));
}

std::string
OperatorToken::toString() const
{
	std::stringstream stream;

	stream << "Op(" << toChar() << ")";

	return (stream.str());
}

OperatorToken::ArithmeticException::ArithmeticException() :
        std::exception(),
        _message("no message")
{
}

OperatorToken::ArithmeticException::ArithmeticException(std::string message) :
        std::exception(),
        _message(message)
{
}

OperatorToken::ArithmeticException::ArithmeticException(const ArithmeticException &other) :
        std::exception(),
        _message(other._message)
{
}

OperatorToken::ArithmeticException::~ArithmeticException() throw ()
{
}

OperatorToken::ArithmeticException&
OperatorToken::ArithmeticException::operator =(const ArithmeticException &other)
{
	if (this != &other)
	{
		this->_message = other._message;
	}

	return (*this);
}

const char*
OperatorToken::ArithmeticException::what() const throw ()
{
	return (_message.c_str());
}
