/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenReader.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:55:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 15:55:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TokenReader.hpp"

TokenReader::TokenReader(void)
{
	this->_list = NULL;
	this->_index = 0;
	this->_depth = 0;
	this->_errorPosition = std::string::npos;
	this->_currentToken = NULL;
	this->_peekToken = NULL;
}

TokenReader::TokenReader(ArrayList &list)
{
	this->_list = &list;

	this->_index = 0;
	this->_depth = 0;
	this->_errorPosition = std::string::npos;

	this->nextToken(); /* Current */
	this->nextToken(); /* Peek */
}

TokenReader::TokenReader(const TokenReader &other)
{
	this->operator =(other);
}

TokenReader::~TokenReader()
{
}

TokenReader&
TokenReader::operator =(const TokenReader &other)
{
	if (this != &other)
	{
		this->_list = other._list;
		this->_index = other._index;
		this->_currentToken = other._currentToken;
		this->_peekToken = other._peekToken;
		this->_error = other._error;
		this->_errorPosition = other._errorPosition;
		this->_depth = other._depth;
	}

	return (*this);
}

void
TokenReader::dive(void)
{
	this->_depth++;
}

bool
TokenReader::surface(void)
{
	return (--this->_depth >= 0);
}

bool
TokenReader::checkToken(TokenType type)
{
	if (this->_currentToken == NULL)
		return (type == TT_END_OF_FILE);

	return (this->_currentToken->type() == type);
}

bool
TokenReader::checkPeek(TokenType type)
{
	if (this->_peekToken == NULL)
		return (type == TT_END_OF_FILE);

	return (this->_peekToken->type() == type);
}

void
TokenReader::nextToken(void)
{
	this->_currentToken = this->_peekToken;
	this->_peekToken = this->_list->get(this->_index++);
}

void
TokenReader::previousToken(void)
{
	this->_peekToken = this->_currentToken;
	this->_currentToken = this->_list->get(this->_index--);
}

bool
TokenReader::abort(std::string error)
{
	return (this->abort(error, this->currentToken()->position()));
}

bool
TokenReader::abortNowhere(std::string error)
{
	return (this->abort(error, std::string::npos));
}

bool
TokenReader::abort(std::string error, std::size_t at)
{
	this->_error = error;
	this->_errorPosition = at;

	return (false);
}

bool
TokenReader::aborted(void)
{
	return (!this->_error.empty() || this->_errorPosition != std::string::npos);
}

std::string
TokenReader::getError(void)
{
	return (this->_error);
}

std::size_t
TokenReader::getErrorPosition(void)
{
	return (this->_errorPosition);
}

Token*
TokenReader::currentToken() const
{
	return this->_currentToken;
}

int
TokenReader::depth() const
{
	return this->_depth;
}

const ArrayList*
TokenReader::list() const
{
	return this->_list;
}
