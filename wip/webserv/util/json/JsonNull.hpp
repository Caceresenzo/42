/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonNull.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:10:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:10:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONNULL_HPP_
# define JSONNULL_HPP_

#include <util/json/JsonValue.hpp>
#include <string>

class JsonNull: public JsonValue
{
	public:
		static const std::string STRING;

	public:
		JsonNull()
		{
		}

		JsonNull(const JsonNull &other)
		{
			(void)other;
		}

		virtual
		~JsonNull()
		{
		}

		JsonNull&
		operator =(const JsonNull &other)
		{
			(void)other;

			return (*this);
		}

		JsonValue*
		clone() const
		{
			return (new JsonNull(*this));
		}

		const Type
		type() const
		{
			return (TYPE_NULL);
		}

		const std::string
		toJsonString() const
		{
			return (STRING);
		}
};

#endif /* JSONNULL_HPP_ */
