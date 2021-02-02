/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestHeaderTooBigException.cpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/status/HTTPRequestHeaderTooBigException.hpp>

HTTPRequestHeaderTooBigException::HTTPRequestHeaderTooBigException() :
		HTTPRequestException()
{
}

HTTPRequestHeaderTooBigException::HTTPRequestHeaderTooBigException(const std::string &message) :
		HTTPRequestException(message)
{
}

HTTPRequestHeaderTooBigException::HTTPRequestHeaderTooBigException(const HTTPRequestHeaderTooBigException &other) :
		HTTPRequestException(other)
{
}

HTTPRequestHeaderTooBigException::~HTTPRequestHeaderTooBigException() throw ()
{
}

HTTPRequestHeaderTooBigException&
HTTPRequestHeaderTooBigException::operator=(const HTTPRequestHeaderTooBigException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
