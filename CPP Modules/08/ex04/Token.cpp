/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:08:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:08:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "Token.hpp"

Token::Token()
{
}

Token::~Token()
{
}

Token::Token(const Token &other)
{
	this->operator =(other);
}

Token&
Token::operator=(const Token &other)
{
	(void)other;

	return (*this);
}

std::string
Token::join(std::vector<Token*> const &tokens)
{
	if (tokens.empty())
		return ("<empty>");

	std::stringstream stream;

	for (size_t index = 0; index < tokens.size(); ++index)
	{
		stream << tokens[index];

		if (index < tokens.size() - 1)
			stream << ' ';
	}

	return (stream.str());
}

std::ostream&
operator <<(std::ostream &stream, const Token *token)
{
	return (stream << token->toString());
}

void
Token::free(std::vector<Token*> &tokens)
{
	while (!tokens.empty())
	{
		delete tokens[tokens.size() - 1];
		tokens.pop_back();
	}
}
