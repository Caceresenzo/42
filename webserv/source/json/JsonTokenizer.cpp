/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonTokenizer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:53:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 18:53:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonToken.hpp>
#include <json/JsonTokenizer.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

JsonTokenizer::JsonTokenizer(void) :
		m_source(),
		m_lineNo(1),
		m_columnNo(0),
		m_minus(false),
		m_dot(false),
		m_start(0),
		m_index(0)
{
}

JsonTokenizer::JsonTokenizer(const std::string &source) :
		m_source(source),
		m_lineNo(1),
		m_columnNo(0),
		m_minus(false),
		m_dot(false),
		m_start(0),
		m_index(0)
{
}

JsonTokenizer::JsonTokenizer(const JsonTokenizer &other) :
		m_source(other.m_source),
		m_lineNo(other.m_lineNo),
		m_columnNo(other.m_columnNo),
		m_minus(other.m_minus),
		m_dot(other.m_dot),
		m_start(other.m_start),
		m_index(other.m_index)
{
}

JsonTokenizer&
JsonTokenizer::operator=(const JsonTokenizer &other)
{
	if (this != &other)
	{
		m_source = other.m_source;
		m_lineNo = other.m_lineNo;
		m_minus = other.m_minus;
		m_dot = other.m_dot;
		m_start = other.m_start;
		m_index = other.m_index;
	}

	return (*this);
}

void
JsonTokenizer::readNumber(char c)
{
	reset();

	if (c == '-')
	{
		m_minus = true;

		c = read();

		if (!std::isdigit(c))
			throwUnexpected(c);
	}

	if (c == '0')
		c = read();
	else
	{
		do
		{
			c = read();
		}
		while (std::isdigit(c));
	}

	if (c == '.')
	{
		m_dot = true;

		long len = -1;
		do
		{
			c = read();
			len++; /* If c is number, -1 will be 0, then whatever will be next, len will be positive */
		}
		while (std::isdigit(c));

		if (len == 0)
			throwUnexpected(c);
	}

	if (c != -1) /* Only if not an EOF */
		--m_index; /* Read too much */
}

void
JsonTokenizer::readString(void)
{
	char c;

	while ((c = read()) != -1)
	{
		// TODO Support escape
		if (c == '"')
			break;
	}

	if (c != '"')
		throwExpected('"', c);
}

const JsonToken*
JsonTokenizer::nextToken(void)
{
	m_start = m_index;
	char c = read();

	while (std::isspace(c))
	{
		if (c == '\r')
			m_columnNo = 0;
		else if (c == ' ')
			m_columnNo++;
		else if (c == '\t')
			m_columnNo += (m_columnNo + 1) % 4;
		else if (c == '\n')
		{
			m_lineNo++;
			m_columnNo = 0;
		}

		m_start = m_index;
		c = read();
	}

	switch (c)
	{
		case '"':
			readString();
			return (JsonToken::STRING);

		case '{':
			return (JsonToken::CURLYOPEN);

		case '[':
			return (JsonToken::SQUAREOPEN);

		case ':':
			return (JsonToken::COLON);

		case ',':
			return (JsonToken::COMMA);

		case 't':
			expectRead((const char*)"true" + 1); /* 't' has already been read */
			return (JsonToken::TRUE);

		case 'f':
			expectRead((const char*)"false" + 1); /* 'f' has already been read */
			return (JsonToken::FALSE);

		case 'n':
			expectRead((const char*)"null" + 1); /* 'n' has already been read */
			return (JsonToken::NULL_);

		case '}':
			return (JsonToken::CURLYCLOSE);

		case ']':
			return (JsonToken::SQUARECLOSE);

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
		case '-':
			readNumber(c);
			return (JsonToken::NUMBER);

		case -1:
			return (JsonToken::END_OF_FILE);

		default:
			throwUnexpected(c);
	}

	return (NULL); /* Should not happen */
}

long
JsonTokenizer::asLong(void) const
{
	std::stringstream sstream;
	sstream.str(asRawString());

	long value;
	sstream >> value;

	return (value);
}

double
JsonTokenizer::asDouble(void) const
{
	std::string raw = asRawString();
	int precision = computePrecision();

	std::stringstream sstream;
	sstream.str(raw);
	sstream << std::fixed << std::setprecision(precision);

	double value;
	sstream >> value;

	return (value);
}

