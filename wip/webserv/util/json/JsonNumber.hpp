/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonNumber.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:10:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:10:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONNUMBER_HPP_
# define JSONNUMBER_HPP_

#include <util/json/JsonValue.hpp>
#include <sstream>
#include <string>

class JsonNumber: public JsonValue
{
	private:
		long m_value;

	public:
		JsonNumber() :
				m_value(0)
		{
		}

		JsonNumber(long value) :
				m_value(value)
		{
		}

		JsonNumber(const JsonNumber &other) :
				m_value(other.m_value)
		{
		}

		virtual
		~JsonNumber()
		{
		}

		JsonNumber&
		operator =(const JsonNumber &other)
		{
			if (this != &other)
				m_value = other.m_value;

			return (*this);
		}

		operator int()
		{
			return (m_value);
		}

		operator int() const
		{
			return (m_value);
		}

		operator long()
		{
			return (m_value);
		}

		operator long() const
		{
			return (m_value);
		}

		JsonValue*
		clone() const
		{
			return (new JsonNumber(*this));
		}

		const Type
		type() const
		{
			return (TYPE_NUMBER);
		}

		const std::string
		toJsonString() const
		{
			std::stringstream sstream;
			sstream << m_value;

			return (sstream.str());
		}
};

#endif /* JSONNUMBER_HPP_ */
