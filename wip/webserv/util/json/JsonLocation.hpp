/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonLocation.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONLOCATION_HPP_
# define JSONLOCATION_HPP_

#include <iostream>
#include <string>

class JsonLocation
{
	public:
		typedef std::string::size_type number;

	private:
		number m_line;
		number m_column;
		number m_index;

	public:
		JsonLocation() :
				m_line(-1),
				m_column(-1),
				m_index(-1)
		{
		}

		JsonLocation(number line, number column, number index) :
				m_line(line),
				m_column(column),
				m_index(index)
		{
		}

		JsonLocation(const JsonLocation &other) :
				m_line(other.m_line),
				m_column(other.m_column),
				m_index(other.m_index)
		{
		}

		JsonLocation&
		operator =(const JsonLocation &other)
		{
			if (this != &other)
			{
				m_line = other.m_line;
				m_column = other.m_column;
				m_index = other.m_index;
			}

			return (*this);
		}

		number
		line() const
		{
			return (m_line);
		}

		number
		column() const
		{
			return (m_column);
		}

		number
		index() const
		{
			return (m_index);
		}

	public:
		static JsonLocation UNKNOWN;
};

std::ostream&
operator<<(std::ostream &stream, const JsonLocation &location);

#endif /* JSONLOCATION_HPP_ */
