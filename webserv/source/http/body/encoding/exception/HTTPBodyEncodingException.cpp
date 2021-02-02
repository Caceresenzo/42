/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPBodyEncodingException.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/body/encoding/exception/HTTPBodyEncodingException.hpp>

HTTPBodyEncodingException::HTTPBodyEncodingException() :
		RuntimeException()
{
}

HTTPBodyEncodingException::HTTPBodyEncodingException(const std::string &message) :
		RuntimeException(message)
{
}

HTTPBodyEncodingException::HTTPBodyEncodingException(const HTTPBodyEncodingException &other) :
		RuntimeException(other)
{
}

HTTPBodyEncodingException::~HTTPBodyEncodingException() throw ()
{
}

HTTPBodyEncodingException&
HTTPBodyEncodingException::operator=(const HTTPBodyEncodingException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
