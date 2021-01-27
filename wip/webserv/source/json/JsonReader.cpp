/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonReader.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:28:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/12 00:28:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IOException.hpp>
#include <sys/errno.h>
#include <json/JsonArray.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonParserEvent.hpp>
#include <json/JsonReader.hpp>
#include <fstream>
#include <sstream>

JsonReader::JsonReader() :
		m_done(false),
		m_parser("")
{
}

JsonReader::JsonReader(const std::string &source) :
		m_done(false),
		m_parser(source)
{
}

JsonReader::JsonReader(const JsonReader &other) :
		m_done(other.m_done),
		m_parser(other.m_parser)
{
}

JsonReader::~JsonReader()
{
}

JsonReader&
JsonReader::operator=(const JsonReader &other)
{
	if (this != &other)
	{
		m_done = other.m_done;
		m_parser = other.m_parser;
	}

	return (*this);
}

JsonValue*
JsonReader::read(void)
{
	markDone();

	if (m_parser.hasNext())
	{
		JsonValue *value = NULL;

		try
		{
			m_parser.next();

			value = m_parser.get();

			m_parser.hasNext();

			return (value);
		}
		catch (...)
		{
			if (value)
				delete value;

			throw;
		}
	}

	throw internalException();
}

JsonStructure*
JsonReader::readStructure(void)
{
	markDone();

	if (m_parser.hasNext())
	{
		JsonStructure *structure = NULL;

		try
		{
			const JsonParserEvent *event = m_parser.next();

			if (JsonParserEvent::START_ARRAY == event)
				structure = m_parser.getArray();
			else if (JsonParserEvent::START_OBJECT == event)
				structure = m_parser.getObject();

			if (structure) /* Reach the internal exception if none match */
			{
				m_parser.hasNext();

				return (structure);
			}
		}
		catch (...)
		{
			if (structure)
				delete structure;

			throw;
		}
	}

	throw internalException();
}

JsonArray*
JsonReader::readArray(void)
{
	markDone();

	if (m_parser.hasNext())
	{
		JsonArray *array = NULL;

		try
		{
			m_parser.next();

			array = m_parser.getArray();

			m_parser.hasNext();

			return (array);
		}
		catch (...)
		{
			if (array)
				delete array;

			throw;
		}
	}

	throw internalException();
}

JsonObject*
JsonReader::readObject(void)
{
	markDone();

	if (m_parser.hasNext())
	{
		JsonObject *object = NULL;

		try
		{
			m_parser.next();

			object = m_parser.getObject();

			m_parser.hasNext();

			return (object);
		}
		catch (...)
		{
			if (object)
				delete object;

			throw;
		}
	}

	throw internalException();
}

JsonReader
JsonReader::fromFile(const std::string &path) throw (IOException)
{
	std::ifstream filestream(path.c_str());
	if (!filestream.is_open())
		throw IOException("Failed to open: " + path, errno);

	std::stringstream buffer;
	buffer << filestream.rdbuf();

	return (JsonReader(buffer.str()));
}
