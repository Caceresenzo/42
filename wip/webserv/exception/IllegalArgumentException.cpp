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
		Exception()
{
}

IllegalArgumentException::IllegalArgumentException(std::string message) :
		Exception(message)
{
}

IllegalArgumentException::IllegalArgumentException(const IllegalArgumentException &other) :
		Exception(other)
{
}

IllegalArgumentException::~IllegalArgumentException() throw ()
{
}

IllegalArgumentException&
IllegalArgumentException::operator =(const IllegalArgumentException &other)
{
	Exception::operator =(other);

	return (*this);
}
