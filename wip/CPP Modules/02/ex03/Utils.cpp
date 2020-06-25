/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

Utils::Utils(void)
{
	return;
}

Utils::Utils(const Utils &other)
{
	*this = other;
}

Utils::~Utils(void)
{
	;
}

Utils&
Utils::operator =(const Utils &other)
{
	(void)other;
	return (*this);
}

bool
Utils::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool
Utils::isDigit(char c)
{
	return ((c >= '0' && c <= '9') || c == '.');
}

bool
Utils::isParenthesis(char c)
{
	return (c == '(' || c == ')');
}

bool
Utils::isWhitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
	        || c == '\v');
}
