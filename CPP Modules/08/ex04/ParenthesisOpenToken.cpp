/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParenthesisOpenToken.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParenthesisOpenToken.hpp"

ParenthesisOpenToken::ParenthesisOpenToken() :
        Token()
{
}

ParenthesisOpenToken::ParenthesisOpenToken(const ParenthesisOpenToken &other) :
        Token(other)
{
	this->operator =(other);
}

ParenthesisOpenToken::~ParenthesisOpenToken()
{
}

ParenthesisOpenToken&
ParenthesisOpenToken::operator=(const ParenthesisOpenToken &other)
{
	Token::operator =(other);

	return (*this);
}

Token*
ParenthesisOpenToken::clone() const
{
	return (new ParenthesisOpenToken(*this));
}

std::string
ParenthesisOpenToken::toString() const
{
	return ("ParOpen");
}
