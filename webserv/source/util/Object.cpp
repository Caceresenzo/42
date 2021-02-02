/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:20:34 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 22:20:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/Object.hpp>
#include <sstream>
#include <typeinfo>

Object::Object()
{
}

Object::Object(const Object &other)
{
	(void)other;
}

Object::~Object()
{
}

Object&
Object::operator=(const Object &other)
{
	(void)other;

	return (*this);
}

std::string
Object::toString() const
{
	std::stringstream stream;

	stream << std::hex << (void*)this;

	return (std::string(typeid(*this).name()) + "[at " + stream.str() + "]");
}
