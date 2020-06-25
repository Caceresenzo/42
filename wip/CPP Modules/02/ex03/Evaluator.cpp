/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Evaluator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:55:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 15:55:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Evaluator.hpp"

#include "NumberToken.hpp"
#include "ArrayList.hpp"
#include "Fixed.hpp"

Evaluator::Evaluator(void) : TokenReader()
{
}

Evaluator::Evaluator(ArrayList &list) : TokenReader(list)
{
}

Evaluator::Evaluator(const Evaluator &other) : TokenReader(other)
{
}

Evaluator::~Evaluator()
{
}

Evaluator&
Evaluator::operator =(const Evaluator &other)
{
	TokenReader::operator =(other);

	return (*this);
}

bool
Evaluator::hasPrecedence(const Token *o1,
                         const Token *o2)
{
	if (o2->type() == TT_ROUND_BRACKET_OPEN || o2->type() == TT_ROUND_BRACKET_CLOSE)
		return false;

	return (!((o1->type() == TT_ASTERISK || o1->type() == TT_SLASH) && (o2->type() == TT_PLUS || o2->type() == TT_MINUS)));
}

NumberToken*
Evaluator::useOperator(const Token *rightToken,
                       const Token *leftToken,
                       const Token *operatorToken)
{
	Fixed result;

	Fixed left = dynamic_cast<const NumberToken*>(leftToken)->getValue();
	Fixed right = dynamic_cast<const NumberToken*>(rightToken)->getValue();
	TokenType type = operatorToken->type();

	delete leftToken;
	delete rightToken;
	delete operatorToken;

	switch (type)
	{
		case TT_PLUS:
			result = left + right;
			break;

		case TT_MINUS:
			result = left - right;
			break;

		case TT_ASTERISK:
			result = left * right;
			break;

		case TT_SLASH:
			result = left / right;

			if (right.getRawBits() == 0)
				this->abortNowhere("division by zero");

			break;

		default:
			break;
	}
	return (new NumberToken(result));
}

Fixed
Evaluator::evaluate(void)
{
	ArrayList values = ArrayList();
	ArrayList operations = ArrayList();

	while (!this->checkToken(TT_END_OF_FILE) && !this->aborted())
	{
		if (this->checkToken(TT_NUMBER))
			values.push(new NumberToken(*(dynamic_cast<const NumberToken*>(this->currentToken()))));
		else if (this->checkToken(TT_ROUND_BRACKET_OPEN))
			operations.push(new Token(*(this->currentToken())));
		else if (this->checkToken(TT_ROUND_BRACKET_CLOSE))
		{
			while (operations.peek() != NULL && operations.peek()->type() != TT_ROUND_BRACKET_OPEN)
				values.push(this->useOperator(values.pop(), values.pop(), operations.pop()));

			delete operations.pop();
		}
		else if (Token::isOperator(this->currentToken()->type()))
		{
			while (!this->aborted() && !operations.empty() && Evaluator::hasPrecedence(this->currentToken(), operations.peek()))
				values.push(this->useOperator(values.pop(), values.pop(),operations.pop()));

			operations.push(new Token(*(this->currentToken())));
		}

		if (!this->aborted())
			this->nextToken();
	}

	while (!this->aborted() && !operations.empty())
		values.push(this->useOperator(values.pop(), values.pop(), operations.pop()));

	const NumberToken *token = dynamic_cast<const NumberToken*>(values.pop());
	Fixed result = token->getValue();

	delete token;

	return (result);
}
