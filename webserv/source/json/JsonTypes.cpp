/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonTypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 02:16:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/16 02:16:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonType.hpp>
#include <json/JsonValue.hpp>
#include <json/JsonArray.hpp>
#include <json/JsonBoolean.hpp>
#include <json/JsonDecimal.hpp>
#include <json/JsonNull.hpp>
#include <json/JsonNumber.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonReader.hpp>
#include <json/JsonString.hpp>

#define REGISTER_JSON_TYPE_TRAITS(cls, jsonType) \
	const char* JsonTypeTraits<cls>::name = #cls; \
	const JsonValue::Type JsonTypeTraits<cls>::type = jsonType; \
	const char* JsonTypeTraits<cls>::typeString = JsonValue::typeStringStorage()[jsonType].c_str();

REGISTER_JSON_TYPE_TRAITS(JsonArray, JsonValue::TYPE_ARRAY);
REGISTER_JSON_TYPE_TRAITS(JsonObject, JsonValue::TYPE_OBJECT);
REGISTER_JSON_TYPE_TRAITS(JsonString, JsonValue::TYPE_STRING);
REGISTER_JSON_TYPE_TRAITS(JsonNumber, JsonValue::TYPE_NUMBER);
REGISTER_JSON_TYPE_TRAITS(JsonDecimal, JsonValue::TYPE_DECIMAL);
REGISTER_JSON_TYPE_TRAITS(JsonBoolean, JsonValue::TYPE_BOOLEAN);
REGISTER_JSON_TYPE_TRAITS(JsonNull, JsonValue::TYPE_NULL);
