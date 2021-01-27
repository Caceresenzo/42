/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonValue.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:50:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 18:50:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONVALUE_HPP_
# define JSONVALUE_HPP_

#include <iostream>
#include <string>

class JsonValue
{
	public:
		enum Type
		{
			TYPE_ARRAY,
			TYPE_OBJECT,
			TYPE_STRING,
			TYPE_NUMBER,
			TYPE_DECIMAL,
			TYPE_BOOLEAN,
			TYPE_NULL, /* DO NOT CHANGE ORDER, typeStringStorage() depends on it. */
			TYPE__SIZE
		};

	public:
		virtual
		~JsonValue()
		{
		}

		virtual JsonValue*
		clone() const = 0;

		virtual Type
		type() const = 0;

		const std::string&
		typeString() const;

		virtual const std::string
		toJsonString() const = 0;

		virtual bool
		equals(const JsonValue &other) const = 0;

		inline bool
		operator==(const JsonValue &other) const
		{
			if (type() != other.type())
				return (false);

			return (equals(other));
		}

		inline bool
		operator!=(const JsonValue &other) const
		{
			return (!operator==(other));
		}

		template<typename T>
			inline bool
			instanceOf() const
			{
				return (!!cast<T>());
			}

		template<typename T>
			inline T*
			cast()
			{
				return (dynamic_cast<T*>(this));
			}

		template<typename T>
			inline const T*
			cast() const
			{
				return (dynamic_cast<const T*>(this));
			}

	public:
		static const std::string*
		typeStringStorage();
};

std::ostream&
operator <<(std::ostream &stream, const JsonValue &jsonValue);

#endif
