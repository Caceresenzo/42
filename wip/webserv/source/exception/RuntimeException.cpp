/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuntimeException.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RuntimeException.hpp"

RuntimeException::RuntimeException() :
		Exception()
{
}

RuntimeException::RuntimeException(const std::string &message) :
		Exception(message)
{
}

RuntimeException::RuntimeException(const RuntimeException &other) :
		Exception(other)
{
}

RuntimeException::~RuntimeException() throw ()
{
}

RuntimeException&
RuntimeException::operator=(const RuntimeException &other)
{
	Exception::operator=(other);

	return (*this);
}
