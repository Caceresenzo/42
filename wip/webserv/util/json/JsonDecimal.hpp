/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonDecimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONDECIMAL_HPP_
# define JSONDECIMAL_HPP_

#include <util/json/JsonValue.hpp>
#include <iomanip>
#include <sstream>
#include <string>

class JsonDecimal :
		public JsonValue
{
	private:
		double m_value;
		int m_precision;

	public:
		JsonDecimal() :
				m_value(0.0),
				m_precision(1)
		{
		}

		JsonDecimal(double value) :
				m_value(value),
				m_precision(1)
		{
		}
		JsonDecimal(double value, int precision) :
				m_value(value),
				m_precision(precision)
		{
		}

		JsonDecimal(const JsonDecimal &other) :
				m_value(other.m_value),
				m_precision(other.m_precision)
		{
		}

		virtual
		~JsonDecimal()
		{
		}

		JsonDecimal&
		operator =(const JsonDecimal &other)
		{
			if (this != &other)
			{
				m_value = other.m_value;
				m_precision = other.m_precision;
			}

			return (*this);
		}

		operator float()
		{
			return (m_value);
		}

		operator float() const
		{
			return (m_value);
		}

		operator double()
		{
			return (m_value);
		}

		operator double() const
		{
			return (m_value);
		}

		JsonValue*
		clone() const
		{
			return (new JsonDecimal(*this));
		}

		const Type
		type() const
		{
			return (TYPE_DECIMAL);
		}

		const std::string
		toJsonString() const
		{
			std::stringstream sstream;
			sstream << std::fixed << std::setprecision(m_precision) << m_value;

			return (sstream.str());
		}
};

#endif /* JSONDECIMAL_HPP_ */
