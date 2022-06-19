/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseException.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:30:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:30:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseException.hpp"

ParseException::ParseException(void) :
		Exception(),
		m_at(std::string::npos)
{
}

ParseException::ParseException(const std::string &message) :
		Exception(message),
		m_at(std::string::npos)
{
}

ParseException::ParseException(const std::string &message, std::string::size_type at) :
		Exception(message),
		m_at(at)
{
}

ParseException::ParseException(const std::string &message, const StringReader &reader) :
		Exception(message),
		m_at(reader.get_index())
{
}

ParseException::ParseException(const ParseException &other) :
		Exception(other),
		m_at(other.m_at)
{
}

ParseException::~ParseException() throw ()
{
}

ParseException&
ParseException::operator =(const ParseException &other)
{
	Exception::operator =(other);

	return (*this);
}

const std::string::size_type&
ParseException::at() const
{
	return (m_at);
}
