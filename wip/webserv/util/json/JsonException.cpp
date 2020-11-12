/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/json/JsonException.hpp>

JsonException::JsonException() :
		Exception()
{
}

JsonException::JsonException(const std::string &message) :
		Exception(message)
{
}

JsonException::JsonException(const JsonException &other) :
		Exception(other)
{
}

JsonException::~JsonException() throw ()
{
}

JsonException&
JsonException::operator=(const JsonException &other)
{
	Exception::operator=(other);

	return (*this);
}
