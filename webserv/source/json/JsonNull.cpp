/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonNull.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:10:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:10:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonNull.hpp>

const std::string JsonNull::STRING = "null";

JsonNull::JsonNull()
{
}

JsonNull::JsonNull(const JsonNull &other)
{
	(void)other;
}

JsonNull::~JsonNull()
{
}

JsonNull&
JsonNull::operator =(const JsonNull &other)
{
	(void)other;

	return (*this);
}

JsonValue*
JsonNull::clone() const
{
	return (new JsonNull(*this));
}

JsonNull::Type
JsonNull::type() const
{
	return (TYPE_NULL);
}

const std::string
JsonNull::toJsonString() const
{
	return (STRING);
}

bool
JsonNull::equals(const JsonValue &other) const
{
	if (dynamic_cast<JsonNull const*>(&other))
		return (true);

	return (false);
}
