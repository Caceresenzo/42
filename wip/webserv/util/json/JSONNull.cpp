/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONNull.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:38:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:38:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JSONNull.hpp>

JSONNull::JSONNull(void)
{
}

JSONNull::JSONNull(const JSONNull &other)
{
	(void)other;
}

JSONNull::~JSONNull()
{
}

JSONNull&
JSONNull::operator =(const JSONNull &other)
{
	(void)other;

	return (*this);
}

std::string
JSONNull::toJsonString() const
{
	return ("null");
}

JSONBase*
JSONNull::clone() const
{
	return (new JSONNull(*this));
}
