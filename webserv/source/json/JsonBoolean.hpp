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

#include <json/JsonValue.hpp>
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
		JsonBoolean();
		JsonBoolean(bool value);
		JsonBoolean(const JsonBoolean &other);

		virtual
		~JsonBoolean();

		JsonBoolean&
		operator =(const JsonBoolean &other);

		operator bool();
		operator bool() const;

		JsonValue*
		clone() const;

		Type
		type() const;

		const std::string
		toJsonString() const;

		bool
		equals(const JsonValue &other) const;
};

#endif /* JSONBOOLEAN_HPP_ */
