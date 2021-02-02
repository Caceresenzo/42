/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoSuchElementException.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NoSuchElementException.hpp"

NoSuchElementException::NoSuchElementException(void) :
		RuntimeException()
{
}

NoSuchElementException::NoSuchElementException(const std::string &message) :
		RuntimeException(message)
{
}

NoSuchElementException::NoSuchElementException(const NoSuchElementException &other) :
		RuntimeException(other)
{
}

NoSuchElementException::~NoSuchElementException() throw ()
{
}

NoSuchElementException&
NoSuchElementException::operator=(const NoSuchElementException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
