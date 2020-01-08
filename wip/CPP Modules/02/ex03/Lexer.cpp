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

#include <sstream>

#include "Lexer.hpp"
#include "Token.hpp"
#include "Utils.hpp"

#define ERR_CHECK if (error) { return ; }

Lexer::Lexer(void)
{
	this->expression = "";
	this->index = 0;
	this->depth = 0;
	this->error = false;
};

Lexer::Lexer(std::string expression)
{
	this->expression = expression;
	this->index = 0;
	this->depth = 0;
	this->error = false;
};

Lexer::Lexer(const Lexer &other)
{
	*this = other;
}

Lexer::~Lexer(void)
{
	return ;
}

Lexer &
Lexer::operator =(const Lexer &other)
{
	if (this != &other)
	{
		this->expression = other.expression;
		this->index = other.index;
		this->depth = other.depth;
		this->error = other.error;
	}

	return (*this);
}

char
Lexer::eat(void)
{
	char current;

	while (index < expression.length())
	{
		current = expression.at(index);
		index++;

		if (Utils::isWhitespace(current))
		{
			continue ;
		}

		if (Utils::isDigit(current) || Utils::isOperator(current) || Utils::isParenthesis(current))
		{
			return (current);
		}

		error = true;
		return (LEXER_ERR);
	}

	return (LEXER_EOF);

};

void
Lexer::process(t_list *&lst)
{
	Token *token;
	char c;

	while (true)
	{
		token = NULL;
		c = eat();

		if (c == LEXER_EOF || c == LEXER_ERR)
		{
			return ;
		}
		else
		{
			if (c == '(')
			{
				depth++;

				size_t start = index;

				t_list *new_lst = NULL;
				process(new_lst);

				ERR_CHECK;

				token = new Token(new_lst, start);
			}
			else if (c == ')')
			{
				depth--;

				if (depth < 0)
				{
					error = true;
				}

				return ;
			}
			else if (Utils::isOperator(c))
			{
				token = new Token(c, index);
			}
			else if (Utils::isDigit(c))
			{
				size_t start = index;
				float read = readFloat();

				ERR_CHECK;

				token = new Token(new Fixed(read), start);
			}
		}

		ft_lstadd_back(&lst, ft_lstnew(token));
	}
}

float
Lexer::readFloat(void)
{
	size_t start = --index;
	bool dot = false;

	while (index < expression.length() && Utils::isDigit(expression.at(index)))
	{
		if (expression.at(index) == '.')
		{
			if (!dot)
			{
				dot = true;
			}
			else
			{
				error = true;
			}
		}
		index++;

		if (error)
		{
			return (0.0);
		}
	}

	std::string part = expression.substr(start, index - start);
	std::istringstream stream(part);

	float floatValue = 0;
	stream >> floatValue;

	return (floatValue);
}

bool
Lexer::analyze(t_list *&lst)
{
	process(lst);

	return (!error);
}

std::string
Lexer::getExpression(void)
{
	return (this->expression);
}

size_t
Lexer::getCurrentIndex(void)
{
	return (this->index);
}

int
Lexer::getCurrentDepth(void)
{
	return (this->depth);
}

bool
Lexer::hasFoundError(void)
{
	return (this->error);
}
