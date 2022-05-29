/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:14:21 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:14:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

Exception::Exception() :
		m_message()
{
}

Exception::Exception(const std::string &message) :
		m_message(message)
{
}

Exception::Exception(const Exception &other) :
		m_message(other.m_message)
{
}

Exception::~Exception() throw ()
{
}

Exception&
Exception::operator =(const Exception &other)
{
	if (this != &other)
		m_message = other.m_message;

	return (*this);
}

const std::string&
Exception::message() const
{
	return (m_message);
}

const char*
Exception::what() const throw ()
{
	return (m_message.c_str());
}
