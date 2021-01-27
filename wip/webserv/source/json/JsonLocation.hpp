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
		JsonLocation(void);
		JsonLocation(number line, number column, number index);
		JsonLocation(const JsonLocation &other);

		virtual
		~JsonLocation(void);

		JsonLocation&
		operator =(const JsonLocation &other);

		number
		line(void) const;

		number
		column(void) const;

		number
		index(void) const;

	public:
		static JsonLocation UNKNOWN;
};

std::ostream&
operator<<(std::ostream &stream, const JsonLocation &location);

#endif /* JSONLOCATION_HPP_ */
