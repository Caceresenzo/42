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

#include <json/JsonValue.hpp>
#include <sstream>
#include <string>

class JsonNumber :
		public JsonValue
{
	private:
		long m_value;

	public:
		JsonNumber();
		JsonNumber(long value);
		JsonNumber(const JsonNumber &other);

		virtual
		~JsonNumber();

		JsonNumber&
		operator =(const JsonNumber &other);

		operator int();
		operator int() const;
		operator long();
		operator long() const;

		JsonValue*
		clone() const;

		Type
		type() const;

		const std::string
		toJsonString() const;

		bool
		equals(const JsonValue &other) const;
};

#endif /* JSONNUMBER_HPP_ */
