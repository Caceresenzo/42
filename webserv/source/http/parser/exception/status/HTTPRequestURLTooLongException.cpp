/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestURLTooLongException.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/status/HTTPRequestURLTooLongException.hpp>

HTTPRequestURLTooLongException::HTTPRequestURLTooLongException() :
		HTTPRequestException()
{
}

HTTPRequestURLTooLongException::HTTPRequestURLTooLongException(const std::string &message) :
		HTTPRequestException(message)
{
}

HTTPRequestURLTooLongException::HTTPRequestURLTooLongException(const HTTPRequestURLTooLongException &other) :
		HTTPRequestException(other)
{
}

HTTPRequestURLTooLongException::~HTTPRequestURLTooLongException() throw ()
{
}

HTTPRequestURLTooLongException&
HTTPRequestURLTooLongException::operator=(const HTTPRequestURLTooLongException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
