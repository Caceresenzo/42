/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:05:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 14:05:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

#include <string>

Token::Token()
{
	this->_type = TT_END_OF_FILE;
	this->_position = std::string::npos;
}

Token::Token(TokenType type)
{
	this->_type = type;
	this->_position = std::string::npos;
}

Token::~Token()
{
	;
}

Token::Token(const Token &other)
{
	this->operator =(other);
}

Token&
Token::operator=(const Token &other)
{
	if (this != &other)
	{
		this->_type = other._type;
		this->_position = other._position;
	}

	return (*this);
}

TokenType
Token::type() const
{
	return (this->_type);
}

std::string
Token::name() const
{
	return (Token::typeName(this->_type));
}

std::size_t
Token::position() const
{
	return (this->_position);
}

std::size_t
Token::position(std::size_t position)
{
	if (this->_position == std::string::npos)
		this->_position = position;

	return (this->_position);
}

std::string const
Token::toString(void) const
{
	return ("Token[type=" + Token::typeName(this->_type) + "]");
}

bool
Token::isOperator(TokenType type)
{
	return (type == TT_PLUS || type == TT_MINUS || type == TT_ASTERISK
	        || type == TT_SLASH);
}

std::string
Token::typeName(TokenType type)
{
	return (((std::string[]) {
		"END OF FILE",
		"NUMBER",
		"PLUS",
		"MINUS",
		"ASTERISK",
		"SLASH",
		"ROUND BRACKET OPEN",
		"ROUND BRACKET CLOSE",
		"__SIZE"
	})[(int) type + 1]);
}
