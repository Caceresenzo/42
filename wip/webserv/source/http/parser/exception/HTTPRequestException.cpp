/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestException.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/HTTPRequestException.hpp>

HTTPRequestException::HTTPRequestException() :
		RuntimeException()
{
}

HTTPRequestException::HTTPRequestException(const std::string &message) :
		RuntimeException(message)
{
}

HTTPRequestException::HTTPRequestException(const HTTPRequestException &other) :
		RuntimeException(other)
{
}

HTTPRequestException::~HTTPRequestException() throw ()
{
}

HTTPRequestException&
HTTPRequestException::operator=(const HTTPRequestException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
