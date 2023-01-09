/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IllegalStateException.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lang/IllegalStateException.hpp>

IllegalStateException::IllegalStateException(void) :
		RuntimeException()
{
}

IllegalStateException::IllegalStateException(const std::string &message) :
		RuntimeException(message)
{
}

IllegalStateException::IllegalStateException(const IllegalStateException &other) :
		RuntimeException(other)
{
}

IllegalStateException::~IllegalStateException() throw ()
{
}

IllegalStateException&
IllegalStateException::operator=(const IllegalStateException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
