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

#include <json/JsonValue.hpp>
#include <string>

class JsonNull :
		public JsonValue
{
	public:
		static const std::string STRING;

	public:
		JsonNull();
		JsonNull(const JsonNull &other);

		virtual
		~JsonNull();

		JsonNull&
		operator =(const JsonNull &other);

		JsonValue*
		clone() const;

		Type
		type() const;

		const std::string
		toJsonString() const;

		bool
		equals(const JsonValue &other) const;
};

#endif /* JSONNULL_HPP_ */
