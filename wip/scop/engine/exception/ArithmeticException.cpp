/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticException.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/exception/ArithmeticException.hpp>

ArithmeticException::ArithmeticException() :
		RuntimeException()
{
}

ArithmeticException::ArithmeticException(const std::string &message) :
		RuntimeException(message)
{
}

ArithmeticException::ArithmeticException(const ArithmeticException &other) :
		RuntimeException(other)
{
}

ArithmeticException::~ArithmeticException() throw ()
{
}

ArithmeticException&
ArithmeticException::operator=(const ArithmeticException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
