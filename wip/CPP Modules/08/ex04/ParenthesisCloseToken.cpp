/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParenthesisCloseToken.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParenthesisCloseToken.hpp"

ParenthesisCloseToken::ParenthesisCloseToken() :
        Token()
{
}

ParenthesisCloseToken::ParenthesisCloseToken(const ParenthesisCloseToken &other) :
        Token(other)
{
	this->operator =(other);
}

ParenthesisCloseToken::~ParenthesisCloseToken()
{
}

ParenthesisCloseToken&
ParenthesisCloseToken::operator=(const ParenthesisCloseToken &other)
{
	Token::operator =(other);

	return (*this);
}

Token*
ParenthesisCloseToken::clone() const
{
	return (new ParenthesisCloseToken(*this));
}

std::string
ParenthesisCloseToken::toString() const
{
	return ("ParClose");
}
