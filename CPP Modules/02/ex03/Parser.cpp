/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:55:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 15:55:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <iostream>

Parser::Parser(void) : TokenReader()
{
}

Parser::Parser(ArrayList &list) : TokenReader(list)
{
}

Parser::Parser(const Parser &other) : TokenReader(other)
{
}

Parser::~Parser()
{
}

Parser&
Parser::operator =(const Parser &other)
{
	TokenReader::operator =(other);

	return (*this);
}

bool
Parser::parseLine()
{
	if (this->currentToken() == NULL)
		return (true);

	if (this->parseExpression() && this->depth() != 0)
		return (this->abort("bracket open but never closed"));

	return (true);
}

bool
Parser::parseExpression()
{
	if (Token::isOperator(this->currentToken()->type()))
		return (this->abort("operator at start of expression"));

	while (true)
	{
		if (!this->parseExpressionBody())
			return (false);

		if (this->checkToken(TT_END_OF_FILE))
			break;
	}

	return (this->parseExpressionBody());
}

bool
Parser::parseExpressionBody()
{
	if (this->checkToken(TT_END_OF_FILE))
	{
		if (this->depth() != 0)
			return (this->abort("bracket open but never closed"));

		return (true);
	}
	else if (this->checkToken(TT_ROUND_BRACKET_OPEN))
	{
		this->nextToken();

		if (this->checkToken(TT_ROUND_BRACKET_CLOSE))
			return (this->abort("empty brackets"));

		this->dive();

		return (this->parseExpression());
	}
	else if (this->checkToken(TT_ROUND_BRACKET_CLOSE))
	{
		this->nextToken();

		bool r;
		if (!(r = this->surface()))
		{
			this->abort("close bracket but never open");
		}
		else
		{
			if (this->checkToken(TT_ROUND_BRACKET_OPEN))
				return (this->abort("multiple group"));
			else if (!this->checkToken(TT_END_OF_FILE)
						&& (!Token::isOperator(this->currentToken()->type())
							&& !this->checkToken(TT_ROUND_BRACKET_CLOSE)))
				return (this->abort("need operator after brackets"));
		}

		return (r);
	}
	else if (this->checkToken(TT_NUMBER))
	{
		this->nextToken();

		if (this->checkToken(TT_NUMBER))
			return (this->abort("multiple number"));

		return (true);
	}
	else if (Token::isOperator(this->currentToken()->type()))
	{
		TokenType type = this->currentToken()->type();

		this->nextToken();

		TokenType now = this->currentToken()->type();

		if (Token::isOperator(type) && Token::isOperator(now))
			return (this->abort("multiple operator: " + Token::typeName(now)));

		if (this->checkToken(TT_END_OF_FILE))
			return (this->abort("missing number or group after operator"));

		return (true);
	}

	this->nextToken();

	return (this->abort("unexpected token"));
}
