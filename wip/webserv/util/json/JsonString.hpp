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

#include <util/json/JsonUtils.hpp>
#include <util/json/JsonValue.hpp>
#include <string>

class JsonString: public JsonValue
{
	private:
		std::string m_value;

	public:
		JsonString() :
				m_value()
		{
		}

		JsonString(const char *value) :
				m_value(value)
		{
		}

		JsonString(const std::string &value) :
				m_value(value)
		{
		}

		JsonString(const JsonString &other) :
				m_value(other.m_value)
		{
		}

		virtual
		~JsonString()
		{
		}

		JsonString&
		operator =(const JsonString &other)
		{
			if (this != &other)
				m_value = other.m_value;

			return (*this);
		}

		operator std::string()
		{
			return (m_value);
		}

		operator std::string() const
		{
			return (m_value);
		}

		JsonValue*
		clone() const
		{
			return (new JsonString(*this));
		}

		const Type
		type() const
		{
			return (TYPE_STRING);
		}

		const std::string
		toJsonString() const
		{
			return (JsonUtils::escapeString(m_value));
		}
};

#endif /* JSONSTRING_HPP_ */
