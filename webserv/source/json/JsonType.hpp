/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonType.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 20:12:14 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/02 20:12:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONTYPE_HPP_
# define JSONTYPE_HPP_

#include <json/JsonArray.hpp>
#include <json/JsonBoolean.hpp>
#include <json/JsonDecimal.hpp>
#include <json/JsonNull.hpp>
#include <json/JsonNumber.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonString.hpp>
#include <json/JsonValue.hpp>
#include <string>

template<typename T>
	struct JsonTypeTraits
	{
	};

#define FORWARD_DECLARE_JSON_TYPE_TRAITS(cls) \
    template<> \
		struct JsonTypeTraits<cls> \
		{ \
			static const char *name; \
			static const JsonValue::Type type; \
			static const char *typeString; \
		};

FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonArray);
FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonObject);
FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonString);
FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonNumber);
FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonDecimal);
FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonBoolean);
FORWARD_DECLARE_JSON_TYPE_TRAITS(JsonNull);

#endif /* JSONTYPE_HPP_ */
