/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void)
{
	this->tokens = NULL;

	this->problematicToken = NULL;
	this->errorReason = "None";
}

Parser::Parser(Token **tokens)
{
	this->tokens = tokens;

	this->problematicToken = NULL;
	this->errorReason = "None";
}

Parser::Parser(const Parser &other)
{
	*this = other;
}

Parser::~Parser(void)
{
	return ;
}

Parser &
Parser::operator =(const Parser &other)
{
	if (this != &other)
	{
		this->tokens = other.tokens;
		this->problematicToken = other.problematicToken;
		this->errorReason = other.errorReason;
	}

	return (*this);
}

bool
Parser::parse(void)
{
	validate(tokens);

	return (!hasFoundError());
}

void
Parser::validate(Token **tokens)
{
	Token *token;

	if (tokens == NULL)
	{
		return ;
	}

	size_t size = Token::size(tokens);
	if (size == 0)
	{
		return ;
	}

	if ((token = tokens[0])->getKind() == kind_operator)
	{
		setError(token, "Operator at the beginning");
		return ;
	}

	size_t index = 0;
	TokenKind previous = (TokenKind)-1;
	while ((token = tokens[index]))
	{
		TokenKind current = token->getKind();

		if (previous == (TokenKind)-1)
		{
			previous = current;
		}
		else
		{
			if (previous == current)
			{
				setError(token, ((std::string []) {
					"Multiple operator",
					"Multiple litteral",
					"Multiple group",
				})[current]);
				return ;
			}
			else if (previous == kind_number && current == kind_list)
			{
				setError(token, "Number followed by group");
				return ;
			}
			else if (previous == kind_list && current == kind_number)
			{
				setError(token, "Group followed by number");
				return ;
			}

			previous = current;
		}
		if (current == kind_list)
		{
			validate(token->asArrayList());
		}

		index++;
	}

	if ((token = tokens[size - 1])->getKind() == kind_operator)
	{
		setError(token, "Operator at the end");
		return ;
	}
}

void
Parser::setError(Token *problematicToken, std::string errorReason)
{
	this->problematicToken = problematicToken;
	this->errorReason = errorReason;
}

bool
Parser::hasFoundError(void)
{
	return (this->problematicToken != NULL);
}

Token *
Parser::getProblematicToken(void)
{
	return (this->problematicToken);
}

std::string
Parser::getErrorReason(void)
{
	return (this->errorReason);
}
