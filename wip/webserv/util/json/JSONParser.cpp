/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONParser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:02:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/23 17:02:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_ctype.h>
#include <util/json/JSONException.hpp>
#include <util/json/JSONParser.hpp>
#include <string>
#include <sstream>

JSONParser::JSONParser() :
		m_source(),
		m_index(-1)
{
}

JSONParser::JSONParser(const std::string &source) :
		m_source(source),
		m_index(-1)
{
}

JSONParser::JSONParser(const JSONParser &other) :
		m_source(other.m_source),
		m_index(other.m_index)
{
}

JSONParser::~JSONParser()
{
}

JSONParser&
JSONParser::operator =(const JSONParser &other)
{
	if (this != &other)
	{
		m_source = other.m_source;
		m_index = other.m_index;
	}

	return (*this);
}

JSONType
JSONParser::parse(void)
{
	m_index = 0;
	return (parseElement());
}

void
JSONParser::skipWhitespaces(void)
{
	while (m_index < m_source.size() && std::isspace(m_source.at(m_index)))
		m_index++;
}

char
JSONParser::peek(void)
{
	if (m_index > m_source.size())
		throwException("out of bouds (peek)");

	if (m_index == m_source.size())
		return (0);

	return (m_source.at(m_index));
}

char
JSONParser::next(bool escape)
{
	if (m_index >= m_source.size())
		throwException("out of bouds (next)");

	char c = m_source.at(m_index++);

	if (escape && c == '\\')
	{
		if (m_index >= m_source.size())
			throwException("out of bouds (escaped next)");

		c = m_source.at(m_index++);
	}

	return (c);
}

JSONType
JSONParser::parseElement(void)
{
	skipWhitespaces();

	switch (peek())
	{
		case 'f':
		case 't':
			return parseBoolean();

		case 'n':
			return parseNull();

		case '"':
			return parseString();

		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return parseNumber();

		default:
			throwException("unexpected");
	}

	return (JSONType());
}

JSONType
JSONParser::parseBoolean(void)
{
	std::string match;
	bool value;

	char c = peek();
	if (c == 't')
	{
		match = "true";
		value = true;
	}
	else if (c == 'f')
	{
		match = "false";
		value = false;
	}
	else
		throwException("invalid boolean start");

	for (size_t i = 0; i < match.size(); i++)
	{
		if (match.at(i) != next(false))
			throwException("unexpected character in boolean");
	}

	expect(E_END | E_COMA | E_ARRAY_END | E_OBJECT_END);

	return (JSONType(value));
}

JSONType
JSONParser::parseNull(void)
{
	for (size_t i = 0; i < 4; i++)
	{
		char c = next(false);
		if ("null"[i] != c)
			throwException(((std::string("unexpected character in null: ") + c) + " instead of ") + "null"[i]);
	}

	expect(E_END | E_COMA | E_ARRAY_END | E_OBJECT_END);

	return (JSONType((const char*)NULL));
}

JSONType
JSONParser::parseString(void)
{
	std::string value;

	next(false); // "

	char c;
	while ((c = next(true)) != JSON_QUOTE)
		value += c;

	expect(E_END | E_COMA | E_ARRAY_END | E_OBJECT_END | E_QUOTE);

	return (JSONType(value));
}

JSONType
JSONParser::parseNumber(void)
{
	std::string stringValue;
	char c;

	expect(E_NUMBER | E_MINUS);

	if (peek() == '-')
	{
		stringValue += "-";
		m_index++;
	}

	expect(E_NUMBER);

	while (std::isdigit(c = peek()))
	{
		stringValue += c;
		m_index++;
	}

	expect(E_DOT | E_END | E_COMA | E_ARRAY_END | E_OBJECT_END);

	bool isDouble;
	if ((isDouble = (c == '.')))
	{
		stringValue += '.';
		m_index++;

		expect(E_NUMBER);

		while (std::isdigit(c = peek()))
		{
			stringValue += c;
			m_index++;
		}
	}

	expect(E_END | E_COMA | E_ARRAY_END | E_OBJECT_END);

	std::stringstream stream;
	stream << stringValue;

	if (isDouble)
	{
		double value;
		stream >> value;

		return (JSONType(value));
	}
	else
	{
		long value;
		stream >> value;

		return (JSONType(value));
	}
}

JSONType
JSONParser::parseArray(void)
{
}

JSONType
JSONParser::parseObject(void)
{
}

void
JSONParser::expect(int mask)
{
	char c;
	if (m_index == m_source.size())
		c = 0;
	else
		c = m_source.at(m_index);

	bool ok = false;
	ok |= (mask & E_NULL) && c == 'n';
	ok |= (mask & E_TRUE) && c == 't';
	ok |= (mask & E_FALSE) && c == 'f';
	ok |= (mask & E_NUMBER) && std::isdigit(c);
	ok |= (mask & E_MINUS) && c == '-';
	ok |= (mask & E_DOT) && c == '.';
	ok |= (mask & E_EXPONENTIAL) && c == 'e';
	ok |= (mask & E_QUOTE) && c == JSON_QUOTE;
	ok |= (mask & E_ARRAY_START) && c == JSON_LEFTBRACKET;
	ok |= (mask & E_ARRAY_END) && c == JSON_RIGHTBRACKET;
	ok |= (mask & E_OBJECT_START) && c == JSON_LEFTBRACE;
	ok |= (mask & E_OBJECT_END) && c == JSON_RIGHTBRACE;
	ok |= (mask & E_COLON) && c == ':';
	ok |= (mask & E_COMA) && c == ',';
	ok |= (mask & E_END) && c == 0;

	if (!ok)
	{
		static std::string expected[32] = { //
		"null", //
		"true", //
		"false", //
		"number", //
		"minus", //
		"dot", //
		"exponential", //
		"quote", //
		"[", //
		"]", //
		"{", //
		"}", //
		":", //
		",", //
		"(end)", //
		};

		std::string line;
		for (int i = 0; i < 32; i++)
		{
			if (mask & (1 << i))
				line += expected[i] + ", ";
		}

		throwException("unexpected: expected " + line + " but got: " + c);
	}
}

void
JSONParser::throwException(std::string message)
{
	throw JSONException(message, m_source, m_index);
}
