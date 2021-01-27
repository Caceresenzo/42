/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonValue.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:50:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 18:50:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonValue.hpp>

const std::string&
JsonValue::typeString() const
{
	return (typeStringStorage()[type()]);
}

const std::string*
JsonValue::typeStringStorage()
{
	static std::string strings[TYPE__SIZE] = {
		"ARRAY",
		"OBJECT",
		"STRING",
		"NUMBER",
		"DECIMAL",
		"BOOLEAN",
		"NULL" }; /* DO NOT CHANGE ORDER, depend on the Type type. */

	return ((std::string*)strings);
}

std::ostream&
operator <<(std::ostream &stream, const JsonValue &jsonValue)
{
	return (stream << jsonValue.toJsonString());
}
