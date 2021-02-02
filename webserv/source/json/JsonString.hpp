/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonString.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:18:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 15:18:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONSTRING_HPP_
# define JSONSTRING_HPP_

#include <json/JsonUtils.hpp>
#include <json/JsonValue.hpp>
#include <string>

class JsonString :
		public JsonValue
{
	private:
		std::string m_value;

	public:
		JsonString();
		JsonString(const char *value);
		JsonString(const std::string &value);
		JsonString(const JsonString &other);

		virtual
		~JsonString();

		JsonString&
		operator =(const JsonString &other);

		operator std::string();
		operator std::string() const;

		JsonValue*
		clone() const;

		Type
		type() const;

		const std::string
		toJsonString() const;

		bool
		equals(const JsonValue &other) const;
};

#endif /* JSONSTRING_HPP_ */
