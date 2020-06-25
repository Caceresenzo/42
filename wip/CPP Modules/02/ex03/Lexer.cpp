/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

#include <string>
#include <sstream>

#include "Fixed.hpp"
#include "NumberToken.hpp"
#include "Utils.hpp"

Lexer::Lexer(void)
{
	this->_expression = "";
	this->_currentChar = 0;
	this->_currentPosition = -1;

	this->nextChar();
}

Lexer::Lexer(std::string expression)
{
	this->_expression = expression;
	this->_currentChar = 0;
	this->_currentPosition = -1;

	this->nextChar();
}

Lexer::Lexer(const Lexer &other)
{
	this->operator =(other);
}

Lexer::~Lexer(void)
{
}

Lexer&
Lexer::operator =(const Lexer &other)
{
	if (this != &other)
	{
		this->_expression = other._expression;
		this->_currentChar = other._currentChar;
		this->_currentPosition = other._currentPosition;
		this->_error = other._error;
	}

	return (*this);
}

void
Lexer::nextChar(void)
{
	std::size_t at = ++this->_currentPosition;

	if (at >= this->_expression.length())
		this->_currentChar = '\0';
	else
		this->_currentChar = this->_expression[at];
}

char
Lexer::peek(void)
{
	std::size_t at = this->_currentPosition + 1;

	if (at >= this->_expression.length())
		return '\0';
	return this->_expression[at];
}

void
Lexer::skipWhitespace(void)
{
	while (Utils::isWhitespace(this->_currentChar))
		this->nextChar();
}

Token*
Lexer::getToken(void)
{
	std::size_t start;
	Token *token = NULL;
	std::stringstream ss;
	float x = 0;

	this->skipWhitespace();

	switch (this->_currentChar)
	{
		case '+':
			token = new Token(TT_PLUS);
			break;

		case '-':
			token = new Token(TT_MINUS);
			break;

		case '*':
			token = new Token(TT_ASTERISK);
			break;

		case '/':
			token = new Token(TT_SLASH);
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			start = this->_currentPosition;

			while (Utils::isDigit(this->peek()))
				this->nextChar();

			if (this->peek() == '.')
			{
				this->nextChar();

				if (!Utils::isDigit(this->peek()))
				{
					this->abort("illegal character in number");
					break;
				}

				while (Utils::isDigit(this->peek()))
					this->nextChar();
			}

			ss << this->_expression.substr(start, this->_currentPosition - start + 1);
			ss >> x;

			token = new NumberToken(Fixed(x));

			break;

		case '\0':
			token = new Token(TT_END_OF_FILE);
			break;

		case '(':
			token = new Token(TT_ROUND_BRACKET_OPEN);
			break;

		case ')':
			token = new Token(TT_ROUND_BRACKET_CLOSE);
			break;

		default:
			this->abort("unknown token");
			break;
	}

	if (token != NULL)
		token->position(this->position());
	if (!this->aborted())
		this->nextChar();

	return token;
}

void
Lexer::abort(std::string error)
{
	this->_error = error;
}

bool
Lexer::aborted(void)
{
	return (!this->_error.empty());
}

ssize_t
Lexer::position(void)
{
	return (this->_currentPosition);
}

std::string
Lexer::getError(void)
{
	return (this->_error);
}
