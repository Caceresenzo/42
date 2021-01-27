/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPStatusLine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:53:31 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/20 19:53:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HTTP.hpp>
#include <http/response/HTTPStatusLine.hpp>
#include <util/Convert.hpp>

HTTPStatusLine::HTTPStatusLine(void) :
		m_version(HTTPVersion::HTTP_1_1),
		m_status()
{
}

HTTPStatusLine::HTTPStatusLine(const HTTPStatus &status) :
		m_version(HTTPVersion::HTTP_1_1),
		m_status(&status)
{
}

HTTPStatusLine::HTTPStatusLine(const HTTPVersion &version, const HTTPStatus &status) :
		m_version(version),
		m_status(&status)
{
}

HTTPStatusLine::HTTPStatusLine(const HTTPStatusLine &other) :
		m_version(other.m_version),
		m_status(other.m_status)
{
}

HTTPStatusLine::~HTTPStatusLine()
{
}

HTTPStatusLine&
HTTPStatusLine::operator =(const HTTPStatusLine &other)
{
	if (this != &other)
	{
		m_version = other.m_version;
		m_status = other.m_status;
	}

	return (*this);
}

std::string
HTTPStatusLine::format(void) const
{
	return (m_version.format() + HTTP::SP + Convert::toString(m_status->code()) + HTTP::SP + m_status->reasonPhrase());
}
