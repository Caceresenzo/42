/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnsupportedOperationException.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/exception/UnsupportedOperationException.hpp>

UnsupportedOperationException::UnsupportedOperationException() :
		RuntimeException()
{
}

UnsupportedOperationException::UnsupportedOperationException(const std::string &message) :
		RuntimeException(message)
{
}

UnsupportedOperationException::UnsupportedOperationException(const UnsupportedOperationException &other) :
		RuntimeException(other)
{
}

UnsupportedOperationException::~UnsupportedOperationException() throw ()
{
}

UnsupportedOperationException&
UnsupportedOperationException::operator=(const UnsupportedOperationException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
