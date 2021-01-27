/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IllegalArgumentException.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:30:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IllegalArgumentException.hpp>

IllegalArgumentException::IllegalArgumentException(void) :
		RuntimeException()
{
}

IllegalArgumentException::IllegalArgumentException(const std::string &message) :
		RuntimeException(message)
{
}

IllegalArgumentException::IllegalArgumentException(const IllegalArgumentException &other) :
		RuntimeException(other)
{
}

IllegalArgumentException::~IllegalArgumentException() throw ()
{
}

IllegalArgumentException&
IllegalArgumentException::operator =(const IllegalArgumentException &other)
{
	RuntimeException::operator =(other);

	return (*this);
}
