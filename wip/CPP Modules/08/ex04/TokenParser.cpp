/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:32:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/20 13:32:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TokenParser.hpp"

#include <sstream>
#include <string>

#include "NumericToken.hpp"
#include "OperatorToken.hpp"
#include "ParenthesisCloseToken.hpp"
#include "ParenthesisOpenToken.hpp"

TokenParser::TokenParser() :
        _expr("")
{
}

TokenParser::TokenParser(std::string expr) :
        _expr(expr)
{
}

TokenParser::TokenParser(const TokenParser &other) :
        _expr(other._expr)
{
	this->operator =(other);
}

TokenParser::~TokenParser()
{
}

TokenParser&
TokenParser::operator=(const TokenParser &other)
{
	(void)other;

	return (*this);
}

#define E_NUMERIC	0b00001
#define E_OPERATOR	0b00010
#define E_POPEN		0b00100
#define E_PCLOSE	0b01000
#define E_NONE		0b10000
#define EXPECT_COND(e, type) ((expect & e) && dynamic_cast<type*>(token))

bool
TokenParser::parse(std::vector<Token*> &out) const
{
	int expect = E_NUMERIC | E_POPEN | E_NONE;
	int depth = 0;

	for (size_t index = 0; index < this->_expr.size(); ++index)
	{
		char c = this->_expr.at(index);

		if (std::isspace(c))
			continue;

		Token *token = TokenParser::tokenFromCharacter(c, this->_expr, index);

		if (token == NULL)
			return (TokenParser::errorAt(this->_expr, "unexpected token", index));

		out.push_back(token);

		if (EXPECT_COND(E_NUMERIC, NumericToken))
		{
			expect = E_OPERATOR | E_NONE;

			if (depth != 0)
				expect |= E_PCLOSE;
		}
		else if (EXPECT_COND(E_OPERATOR, OperatorToken))
		{
			expect = E_POPEN | E_NUMERIC;
		}
		else if (EXPECT_COND(E_POPEN, ParenthesisOpenToken))
		{
			expect = E_NUMERIC | E_POPEN;
			depth++;
		}
		else if (EXPECT_COND(E_PCLOSE, ParenthesisCloseToken))
		{
			expect = E_OPERATOR;
			if (--depth == -1)
				return (TokenParser::errorAt(this->_expr, "parenthesis closed but never open", index));

			if (depth != 0)
				expect |= E_PCLOSE;
			else if (depth == 0)
				expect |= E_NONE;
		}
		else
		{
			std::string message = "expected ";

			if ((expect & E_NUMERIC))
				message += "numeric, ";
			if ((expect & E_OPERATOR))
				message += "operator, ";
			if ((expect & E_POPEN))
				message += "parenthesis open, ";
			if ((expect & E_PCLOSE))
				message += "parenthesis close, ";
			if ((expect & E_NONE))
				message += "end of line, ";

			message += "but got: " + token->toString();

			return (TokenParser::errorAt(this->_expr, message, index));
		}
	}

	if (!(expect & E_NONE))
		return (TokenParser::errorAt(this->_expr, "unexpected end of line"));

	if (depth != 0)
		return (TokenParser::errorAt(this->_expr, "parenthesis open but never closed"));

	return (true);
}

#undef E_NUMERIC
#undef E_OPERATOR
#undef E_POPEN
#undef E_PCLOSE
#undef EXPECT_COND

Token*
TokenParser::tokenFromCharacter(char c, std::string expr, size_t &index)
{
	const char *str = expr.c_str();

	if ((c == '-' && std::isdigit(str[index + 1])) || std::isdigit(c))
	{
		size_t start = index;

		if (c == '-')
			index++;

		while (std::isdigit(str[index]))
			index++;

		std::stringstream stream;
		std::string part = expr.substr(start, index - start);

		stream.str(part);

		index--; /* Don't eat too much. */

		int x = 0;
		stream >> x;

		return new NumericToken(x);
	}

	switch (c)
	{
		case '(':
			return (new ParenthesisOpenToken());

		case ')':
			return (new ParenthesisCloseToken());

		case '+':
			return (new OperatorToken(OP_ADD));

		case '-':
			return (new OperatorToken(OP_SUBSTRACT));

		case '*':
			return (new OperatorToken(OP_MULTIPLY));

		case '/':
			return (new OperatorToken(OP_DEVIDE));
	}

	return (NULL);
}

std::string
TokenParser::pretty(std::vector<Token*> &tokens)
{
	std::stringstream stream;

	for (size_t index = 0; index < tokens.size(); ++index)
	{
		Token *token = tokens[index];

		NumericToken *numericToken;
		OperatorToken *operatorToken;

		if ((numericToken = dynamic_cast<NumericToken*>(token)))
			stream << numericToken->value();
		else if ((operatorToken = dynamic_cast<OperatorToken*>(token)))
			stream << operatorToken->toChar();
		else if (dynamic_cast<ParenthesisOpenToken*>(token))
			stream << '(';
		else if (dynamic_cast<ParenthesisCloseToken*>(token))
			stream << ')';

		if (index != tokens.size() - 1)
		{
			Token *next = tokens[index + 1];

			if (!dynamic_cast<ParenthesisOpenToken*>(token) && !dynamic_cast<ParenthesisCloseToken*>(next))
				stream << ' ';
		}
	}

	return (stream.str());
}

bool
TokenParser::errorAt(std::string expr, size_t position)
{
	return (errorAt(expr, "", position));
}

bool
TokenParser::errorAt(std::string expr, std::string error)
{
	return (errorAt(expr, error, expr.size()));
}

bool
TokenParser::errorAt(std::string expr, std::string error, size_t position)
{
	if (error.empty())
	{
		std::cerr << "error at: " << expr << std::endl;
		std::cerr << "          ";
	}
	else
	{
		std::cerr << error << std::endl;
		std::cerr << "at: " << expr << std::endl;
		std::cerr << "    ";
	}

	for (size_t index = 0; index < position; ++index)
		std::cerr << " ";

	std::cerr << "^" << std::endl;

	return (false);
}
