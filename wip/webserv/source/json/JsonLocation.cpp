/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonLocation.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonLocation.hpp>

JsonLocation JsonLocation::UNKNOWN;

JsonLocation::JsonLocation(void) :
		m_line(-1),
		m_column(-1),
		m_index(-1)
{
}

JsonLocation::JsonLocation(number line, number column, number index) :
		m_line(line),
		m_column(column),
		m_index(index)
{
}

JsonLocation::JsonLocation(const JsonLocation &other) :
		m_line(other.m_line),
		m_column(other.m_column),
		m_index(other.m_index)
{
}

JsonLocation::~JsonLocation(void)
{
}

JsonLocation&
JsonLocation::operator =(const JsonLocation &other)
{
	if (this != &other)
	{
		m_line = other.m_line;
		m_column = other.m_column;
		m_index = other.m_index;
	}

	return (*this);
}

JsonLocation::number
JsonLocation::line(void) const
{
	return (m_line);
}

JsonLocation::number
JsonLocation::column(void) const
{
	return (m_column);
}

JsonLocation::number
JsonLocation::index(void) const
{
	return (m_index);
}

std::ostream&
operator<<(std::ostream &stream, const JsonLocation &location)
{
	return (stream << "line: " << location.line() << ", column: " << location.column() << ", index: " << location.index());
}
