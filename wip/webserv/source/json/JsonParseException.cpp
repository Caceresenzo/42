/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonParseException.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:31:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:31:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonParseException.hpp>
#include <sstream>

JsonParseException::JsonParseException() :
		JsonException(),
		m_location()
{
}

JsonParseException::JsonParseException(const std::string &message) :
		JsonException(message),
		m_location()
{
}

JsonParseException::JsonParseException(const std::string &message, const JsonLocation &location) :
		JsonException(message),
		m_location(location)
{
}

JsonParseException::JsonParseException(const JsonParseException &other) :
		JsonException(other),
		m_location(other.m_location)
{
}

JsonParseException::~JsonParseException() throw ()
{
}

JsonParseException&
JsonParseException::operator=(const JsonParseException &other)
{
	Exception::operator=(other);

	if (this != &other)
		m_location = other.m_location;

	return (*this);
}

const JsonLocation&
JsonParseException::location(void) const
{
	return (m_location);
}

JsonParseException
JsonParseException::unexpectedChar(char c, const JsonLocation &location)
{
	std::stringstream sstream;

	sstream << "Unexpected character `";
	sstream << c;
	sstream << "` at ";
	sstream << location;

	return (JsonParseException(sstream.str(), location));
}

JsonParseException
JsonParseException::expectedChar(char got, char expected, const JsonLocation &location)
{
	std::stringstream sstream;

	sstream << "Unexpected character `";

	if (got == -1)
		sstream << "EOF";
	else if (got)
		sstream << got;
	else
		sstream << "\\0";

	sstream << "` (" << ((int)got) << ")` at ";
	sstream << location;
	sstream << ", expected `";
	sstream << expected;
	sstream << "`";

	return (JsonParseException(sstream.str(), location));
}

JsonParseException
JsonParseException::parsing(const JsonToken *token, std::string expectedTokens, const JsonLocation &location)
{
	std::stringstream sstream;

	sstream << "Invalid token `";
	sstream << token->getDisplayable();
	sstream << "` at ";
	sstream << location;
	sstream << ", expected: ";
	sstream << expectedTokens;

	return (JsonParseException(sstream.str(), location));
}

JsonParseException
JsonParseException::expectedEndOfFile(const JsonToken *token, const JsonLocation &location)
{
	std::stringstream sstream;

	sstream << "Expected EOF, but got `";
	sstream << token->getDisplayable();
	sstream << "` at ";
	sstream << location;

	return (JsonParseException(sstream.str(), location));
}
