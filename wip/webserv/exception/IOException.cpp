/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOException.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:20:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:20:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IOException.hpp>
#include <cerrno>

IOException::IOException(void) :
		Exception(strerror(0)),
		m_errorno(0)
{
}

IOException::IOException(int errorno) :
		Exception(strerror(errorno)),
		m_errorno(errorno)
{
}

IOException::IOException(std::string message) :
		Exception(message),
		m_errorno(0)
{
}

IOException::IOException(std::string message, int errorno) :
		Exception(message + ": " + strerror(errorno)),
		m_errorno(errorno)
{
}

IOException::IOException(const IOException &other) :
		Exception(other),
		m_errorno(other.m_errorno)
{
}

IOException::~IOException() throw ()
{
}

IOException&
IOException::operator =(const IOException &other)
{
	if (this != &other)
		m_errorno = other.m_errorno;

	return (*this);
}

int
IOException::errorno() const
{
	return (m_errorno);
}

void
IOException::check()
{
	check(errno);
}

void
IOException::check(int errorno)
{
	if (errorno)
		throw IOException(errorno);
}
