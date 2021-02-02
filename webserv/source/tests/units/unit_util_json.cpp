/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_json.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:05:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/26 00:05:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/test_unit.hpp>
#include <json/JsonArray.hpp>
#include <json/JsonBoolean.hpp>
#include <json/JsonDecimal.hpp>
#include <json/JsonNull.hpp>
#include <json/JsonNumber.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonReader.hpp>
#include <json/JsonString.hpp>
#include <json/JsonValue.hpp>
#include <string>

static JsonValue *g_temporary_storage = NULL;

static JsonValue&
autoDelete(JsonValue *value)
{
	if (g_temporary_storage)
		delete g_temporary_storage;

	return (*(g_temporary_storage = value));
}

static JsonValue&
json(const char *str)
{
	return (autoDelete(JsonReader(str).read()));
}

CASE("json", "parsing number")
{
	ASSERT(json("0").instanceOf<JsonNumber>());
	ASSERT(json("42").instanceOf<JsonNumber>());
	ASSERT(json("-42").instanceOf<JsonNumber>());

	ASSERT(json("0").cast<JsonNumber>()->operator int() == 0);
	ASSERT(json("42").cast<JsonNumber>()->operator int() == 42);
	ASSERT(json("-42").cast<JsonNumber>()->operator int() == -42);

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing decimal")
{
	ASSERT(json("0.0").instanceOf<JsonDecimal>());
	ASSERT(json("4.2").instanceOf<JsonDecimal>());
	ASSERT(json("-4.2").instanceOf<JsonDecimal>());

	ASSERT(json("0.0").cast<JsonDecimal>()->operator double() == 0.0);
	ASSERT(json("4.2").cast<JsonDecimal>()->operator double() == 4.2);
	ASSERT(json("-4.2").cast<JsonDecimal>()->operator double() == -4.2);

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing true")
{
	ASSERT(json("true").instanceOf<JsonBoolean>());
	ASSERT(json("true").cast<JsonBoolean>()->operator bool() == true);

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing false")
{
	ASSERT(json("false").instanceOf<JsonBoolean>());
	ASSERT(json("false").cast<JsonBoolean>()->operator bool() == false);

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing null")
{
	ASSERT(json("null").instanceOf<JsonNull>());

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing string")
{
	ASSERT(json("\"Hello\"").instanceOf<JsonString>());

	ASSERT(json("\"Hello\"").cast<JsonString>()->operator std::string() == "Hello");

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing empty object")
{
	ASSERT(json("{}").instanceOf<JsonObject>());
	ASSERT(json("{}").cast<JsonObject>()->empty());

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "parsing empty array")
{
	ASSERT(json("[]").instanceOf<JsonArray>());
	ASSERT(json("[]").cast<JsonArray>()->empty());

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "simple object")
{
	JsonObject aTemplate;

	aTemplate.put("hello", new JsonString("world"));
	ASSERT(json("{\"hello\": \"world\"}") == aTemplate);

	aTemplate.put("hello", new JsonNumber(42));
	ASSERT(json("{\"hello\": 42}") == aTemplate);

	aTemplate.put("hello", new JsonBoolean(true));
	ASSERT(json("{\"hello\": true}") == aTemplate);

	aTemplate.put("another", new JsonNull());
	ASSERT(json("{\"hello\": true, \"another\": null}") == aTemplate);

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "simple array")
{
	JsonArray aTemplate;

	aTemplate.add(new JsonString("hello"));
	ASSERT(json("[\"hello\"]") == aTemplate);

	aTemplate.add(new JsonNumber(42));
	ASSERT(json("[\"hello\", 42]") == aTemplate);

	aTemplate.add(new JsonBoolean(true));
	ASSERT(json("[\"hello\", 42, true]") == aTemplate);

	aTemplate.add(new JsonNull());
	ASSERT(json("[\"hello\", 42, true, null]") == aTemplate);

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "unfinished string")
{
	ASSERT_EXCEPT(json("\"hello"));

	(void)&autoDelete(NULL);

	return (0);
}

CASE("json", "empty")
{
	ASSERT_EXCEPT(json(""));

	(void)&autoDelete(NULL);

	return (0);
}
