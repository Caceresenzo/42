/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostfixConvertor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:59:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/20 11:59:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PostfixConvertor.hpp"

#include <stddef.h>

#include "NumericToken.hpp"
#include "ParenthesisCloseToken.hpp"
#include "ParenthesisOpenToken.hpp"

PostfixConvertor::PostfixConvertor() :
        _top(0),
        _tokens(NULL)
{
}

PostfixConvertor::PostfixConvertor(std::vector<Token*> *tokens) :
        _top(0),
        _tokens(tokens)
{
}

PostfixConvertor::~PostfixConvertor()
{
}

PostfixConvertor::PostfixConvertor(const PostfixConvertor &other) :
        _top(other._top),
        _tokens(other._tokens),
        _stack(other._stack)
{
	this->operator =(other);
}

PostfixConvertor&
PostfixConvertor::operator=(const PostfixConvertor &other)
{
	if (this != &other)
	{
		this->_top = other._top;
		this->_tokens = other._tokens;
		this->_stack = other._stack;
	}

	return (*this);
}

bool
PostfixConvertor::isEmpty()
{
	return (this->_top == -1);
}

Token*
PostfixConvertor::peek()
{
	if (!this->_stack.empty())
		return (this->_stack.top());

	return (NULL);
}

Token*
PostfixConvertor::pop()
{
	if (!this->_stack.empty())
	{
		this->_top--;

		Token *top = this->_stack.top();

		this->_stack.pop();

		return (top);
	}

	return (NULL);
}

void
PostfixConvertor::push(Token *token)
{
	this->_top++;
	this->_stack.push(token);
}

bool
PostfixConvertor::isOperand(Token *token)
{
	return (dynamic_cast<NumericToken*>(token) != NULL);
}

bool
PostfixConvertor::notGreater(Token *token)
{
	static const char operatorPrecedence[OP__LENGTH] = {
	        1, 1, 2, 2
	};

	OperatorToken *current;
	if (token != NULL && !(current = dynamic_cast<OperatorToken*>(token)))
		return (false);

	Token *peek = this->peek();
	if (peek == NULL)
		return (false);

	OperatorToken *next;
	if (!(next = dynamic_cast<OperatorToken*>(peek)))
		return (false);

	int a = operatorPrecedence[current->type()];
	int b = operatorPrecedence[next->type()];

	return (a <= b);
}

bool
PostfixConvertor::convert(std::vector<Token*> &out)
{
	this->_top = -1;

	for (size_t index = 0; index < this->_tokens->size(); ++index)
	{
		Token *token = (*this->_tokens)[index];

		if (isOperand(token))
			out.push_back(token->clone());
		else if (dynamic_cast<ParenthesisOpenToken*>(token))
			push(token);
		else if (dynamic_cast<ParenthesisCloseToken*>(token))
		{
			while (!isEmpty() && !dynamic_cast<ParenthesisOpenToken*>(peek()))
				out.push_back(pop()->clone());
			if (!isEmpty() && !dynamic_cast<ParenthesisOpenToken*>(peek()))
				return (false);
			else
				pop();
		}
		else
		{
			while (!isEmpty() && notGreater(token))
				out.push_back(pop()->clone());

			push(token);
		}
	}

	while (!isEmpty())
		out.push_back(pop()->clone());

	return (true);
}

PostfixConvertor::PostfixException::PostfixException() :
        std::exception(),
        _message("no message")
{
}

PostfixConvertor::PostfixException::PostfixException(std::string message) :
        std::exception(),
        _message(message)
{
}

PostfixConvertor::PostfixException::PostfixException(const PostfixException &other) :
        std::exception(),
        _message(other._message)
{
}

PostfixConvertor::PostfixException::~PostfixException() throw ()
{
}

PostfixConvertor::PostfixException&
PostfixConvertor::PostfixException::operator =(const PostfixException &other)
{
	if (this != &other)
	{
		this->_message = other._message;
	}

	return (*this);
}

const char*
PostfixConvertor::PostfixException::what() const throw ()
{
	return (_message.c_str());
}
