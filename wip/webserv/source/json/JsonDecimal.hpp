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

#include <json/JsonValue.hpp>
#include <string>

class JsonDecimal :
		public JsonValue
{
	private:
		double m_value;
		int m_precision;

	public:
		JsonDecimal();
		JsonDecimal(double value);
		JsonDecimal(double value, int precision);
		JsonDecimal(const JsonDecimal &other);

		virtual
		~JsonDecimal();

		JsonDecimal&
		operator =(const JsonDecimal &other);

		operator float();
		operator float() const;
		operator double();
		operator double() const;

		JsonValue*
		clone() const;

		Type
		type() const;

		const std::string
		toJsonString() const;

		bool
		equals(const JsonValue &other) const;
};

#endif /* JSONDECIMAL_HPP_ */
