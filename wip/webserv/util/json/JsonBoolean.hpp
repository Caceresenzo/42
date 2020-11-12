/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonBoolean.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONBOOLEAN_HPP_
# define JSONBOOLEAN_HPP_

#include <util/json/JsonValue.hpp>
#include <string>

class JsonBoolean :
		public JsonValue
{
	public:
		static const std::string TRUE;
		static const std::string FALSE;

	private:
		bool m_value;

	public:
		JsonBoolean() :
				m_value(false)
		{
		}

		JsonBoolean(bool value) :
				m_value(value)
		{
		}

		JsonBoolean(const JsonBoolean &other) :
				m_value(other.m_value)
		{
		}

		virtual
		~JsonBoolean()
		{
		}

		JsonBoolean&
		operator =(const JsonBoolean &other)
		{
			if (this != &other)
				m_value = other.m_value;

			return (*this);
		}

		operator bool()
		{
			return (m_value);
		}

		operator bool() const
		{
			return (m_value);
		}

		JsonValue*
		clone() const
		{
			return (new JsonBoolean(*this));
		}

		const Type
		type() const
		{
			return (TYPE_BOOLEAN);
		}

		const std::string
		toJsonString() const
		{
			return (m_value ? TRUE : FALSE);
		}
};

#endif /* JSONBOOLEAN_HPP_ */
