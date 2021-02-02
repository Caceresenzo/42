/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestPayloadTooLargeException.cpp            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/status/HTTPRequestPayloadTooLargeException.hpp>

HTTPRequestPayloadTooLargeException::HTTPRequestPayloadTooLargeException() :
		HTTPRequestException()
{
}

HTTPRequestPayloadTooLargeException::HTTPRequestPayloadTooLargeException(const std::string &message) :
		HTTPRequestException(message)
{
}

HTTPRequestPayloadTooLargeException::HTTPRequestPayloadTooLargeException(const HTTPRequestPayloadTooLargeException &other) :
		HTTPRequestException(other)
{
}

HTTPRequestPayloadTooLargeException::~HTTPRequestPayloadTooLargeException() throw ()
{
}

HTTPRequestPayloadTooLargeException&
HTTPRequestPayloadTooLargeException::operator=(const HTTPRequestPayloadTooLargeException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
