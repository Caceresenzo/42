/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Evaluator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Evaluator.hpp"
#include "Token.hpp"

Evaluator::Evaluator(void)
{
	this->problemPosition = (size_t)-1;
	this->errorReason = "None";
}

Evaluator::Evaluator(const Evaluator &other)
{
	*this = other;
}

Evaluator::~Evaluator(void)
{
	return ;
}

Evaluator &
Evaluator::operator =(const Evaluator &other)
{
	if (this != &other)
	{
		this->problemPosition = other.problemPosition;
		this->errorReason = other.errorReason;
	}

	return (*this);
}

Fixed
Evaluator::evaluate(Token *tokens[], size_t position)
{
	Fixed result;

	size_t size = Token::size(tokens);

	if (tokens != NULL && size != 0)
	{
		char nextOperator = 0;

		int priority = 1;
		while (priority != -1)
		{
			size_t index = 0;

			Token *token;
			while ((token = tokens[index]))
			{
				if (token->getKind() == kind_operator)
				{
					nextOperator = token->asOperatorChar();

					bool can = false;
					can |= (priority == 1) && (nextOperator == '*' || nextOperator == '/');
					can |= (priority == 0) && (nextOperator == '+' || nextOperator == '-');

					if (can)
					{
						Fixed left = evaluate(tokens[index - 1]);
						Fixed right = evaluate(tokens[index + 1]);

						delete tokens[index - 1];
						delete tokens[index + 0];
						delete tokens[index + 1];

						Fixed part = useOperator(left, right, nextOperator, tokens[index + 1]);

						tokens[index - 1] = new Token(new Fixed(part), position);

						for (size_t jndex = 0; true; jndex++)
						{
							if (tokens[index + 2 + jndex] == NULL)
							{
								tokens[index + jndex] = NULL;
								break ;
							}

							tokens[index + jndex] = tokens[index + 2 + jndex];
						}

						index -= 1;
					}
				}

				index++;
			}

			priority--;
		}

		result = evaluate(tokens[0]);
	}

	return (result);
}

Fixed
Evaluator::evaluate(Token *token)
{
	if (token != NULL)
	{
		if (token->getKind() == kind_number)
		{
			return (*(token->asFixed()));
		}
		else if (token->getKind() == kind_list)
		{
			return (evaluate(token->asArrayList(), token->getPositionInString()));
		}
	}

	return (Fixed(0));
}

Fixed
Evaluator::useOperator(Fixed &left, Fixed &right, char operatorChar, Token *token)
{
	switch (operatorChar) {
		case '+':
		{
			return (left + right);
		}

		case '-':
		{
			return (left - right);
		}

		case '*':
		{
			return (left * right);
		}

		case '/':
		{
			if (right.isZero())
			{
				setError(token->getPositionInString(), "Division by 0");

				break ;
			}

			return (left / right);
		}
	}

	return (Fixed(0));
}

void
Evaluator::setError(size_t problemPosition, std::string errorReason)
{
	this->problemPosition = problemPosition;
	this->errorReason = errorReason;
}

bool
Evaluator::hasFoundError(void)
{
	return (this->problemPosition != (size_t)-1);
}

size_t
Evaluator::getProblemPosition(void)
{
	return (this->problemPosition);
}

std::string
Evaluator::getErrorReason(void)
{
	return (this->errorReason);
}
