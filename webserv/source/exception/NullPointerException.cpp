/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NullPointerException.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NullPointerException.hpp"

NullPointerException::NullPointerException(void) :
		RuntimeException()
{
}

NullPointerException::NullPointerException(const std::string &message) :
		RuntimeException(message)
{
}

NullPointerException::NullPointerException(const NullPointerException &other) :
		RuntimeException(other)
{
}

NullPointerException::~NullPointerException() throw ()
{
}

NullPointerException&
NullPointerException::operator=(const NullPointerException &other)
{
	RuntimeException::operator=(other);

	return (*this);
}
