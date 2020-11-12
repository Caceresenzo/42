/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:04:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:04:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/NoSuchElementException.hpp>
#include <util/json/JsonParser.hpp>
#include <util/json/JsonToken.hpp>

JsonParserEvent* /* Handle {, [, value */
JsonParser::NoneContext::nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack)
{
	JsonToken *token = tokenizer.nextToken();

	if (token == JsonToken::CURLYOPEN)
	{
		stack.push(currentContext);
		currentContext = new ObjectContext();

		return (JsonParserEvent::START_OBJECT);
	}
	else if (token == JsonToken::SQUAREOPEN)
	{
		stack.push(currentContext);
		currentContext = new ArrayContext();

		return (JsonParserEvent::START_ARRAY);
	}
	else if (token->isValue())
		return (token->getEvent());

	throw parser.parsingException(token, "{, [, String, Number, true, false, null");
}

JsonParser::ObjectContext::ObjectContext() :
		m_firstValue(true)
{
}

JsonParserEvent*
JsonParser::ObjectContext::nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack)
{
	// Handle 1. }   2. name:value   3. ,name:value
	JsonToken *token = tokenizer.nextToken();
	if (token == JsonToken::END_OF_FILE)
	{
		if (JsonParserEvent::START_OBJECT == currentEvent)
			throw parser.parsingException(token, "String, }");
		else if (JsonParserEvent::KEY_NAME == currentEvent)
			throw parser.parsingException(token, "`:`");
		else
			throw parser.parsingException(token, "`,`, }");
	}
	else if (currentEvent == JsonParserEvent::KEY_NAME)
	{
		// Handle 1. :value
		if (token != JsonToken::COLON)
			throw parser.parsingException(token, "`:`");

		token = tokenizer.nextToken();
		if (token->isValue())
			return token->getEvent();
		else if (token == JsonToken::CURLYOPEN)
		{
			stack.push(currentContext);
			currentContext = new ObjectContext();

			return (JsonParserEvent::START_OBJECT);
		}
		else if (token == JsonToken::SQUAREOPEN)
		{
			stack.push(currentContext);
			currentContext = new ArrayContext();

			return (JsonParserEvent::START_ARRAY);
		}

		throw parser.parsingException(token, "{, [, String, Number, true, false, null");
	}
	else
	{
		// Handle 1. }   2. name   3. ,name
		if (token == JsonToken::CURLYCLOSE)
		{
			delete currentContext;
			currentContext = stack.top();
			stack.pop();

			return JsonParserEvent::END_OBJECT;
		}

		if (m_firstValue)
			m_firstValue = false;
		else
		{
			if (token != JsonToken::COMMA)
				throw parser.parsingException(token, "`,`, }");

			token = tokenizer.nextToken();
		}

		if (token == JsonToken::STRING)
			return JsonParserEvent::KEY_NAME;

		throw parser.parsingException(token, "String");
	}

	return (NULL); /* Should not happen. */
}

JsonParser::ArrayContext::ArrayContext() :
		m_firstValue(true)
{
}

// Handle 1. ]   2. value   3. ,value
JsonParserEvent*
JsonParser::ArrayContext::nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack)
{
	JsonToken *token = tokenizer.nextToken();
	if (token == JsonToken::END_OF_FILE)
	{
		if (JsonParserEvent::START_ARRAY == currentEvent)
			throw parser.parsingException(token, "{, [, String, Number, true, false, null]");

		throw parser.parsingException(token, "`,`, }");
	}

	if (token == JsonToken::SQUARECLOSE)
	{
		delete currentContext;
		currentContext = stack.top();
		stack.pop();

		return (JsonParserEvent::END_ARRAY);
	}

	if (m_firstValue)
		m_firstValue = false;
	else
	{
		if (token != JsonToken::COMMA)
			throw parser.parsingException(token, "`,`, ]");

		token = tokenizer.nextToken();
	}

	if (token->isValue())
		return token->getEvent();
	else if (token == JsonToken::CURLYOPEN)
	{
		stack.push(currentContext);
		currentContext = new ObjectContext();

		return JsonParserEvent::START_OBJECT;
	}
	else if (token == JsonToken::SQUAREOPEN)
	{
		stack.push(currentContext);
		currentContext = new ArrayContext();

		return JsonParserEvent::START_ARRAY;
	}

	throw parser.parsingException(token, "{, [, String, Number, true, false, null");

	return (NULL); /* Should not happen. */
}

JsonParser::JsonParser(const std::string &source) :
		m_currentContext(new NoneContext()),
		m_currentEvent(NULL),
		m_stack(),
		m_tokenizer(source)
{
}
JsonParser::~JsonParser(void)
{
	delete m_currentContext;

	while (!m_stack.empty())
	{
		delete m_stack.top();

		m_stack.pop();
	}
}

std::string
JsonParser::getRawString()
{
	if (m_currentEvent == JsonParserEvent::KEY_NAME || m_currentEvent == JsonParserEvent::VALUE_STRING || m_currentEvent == JsonParserEvent::VALUE_NUMBER)
		return (m_tokenizer.asString());

	throw getException("Raw String", *m_currentEvent);
}

JsonString*
JsonParser::getString()
{
	if (m_currentEvent != JsonParserEvent::JsonParserEvent::VALUE_STRING)
		throw getException("String", *m_currentEvent);

	return (new JsonString(m_tokenizer.asString()));
}

JsonDecimal*
JsonParser::getDecimal()
{
	if (m_currentEvent != JsonParserEvent::VALUE_NUMBER)
		throw getException("Decimal", *m_currentEvent);

	return (new JsonDecimal(m_tokenizer.asDouble(), m_tokenizer.computePrecision())); // TODO might be too tiny
}

JsonNumber*
JsonParser::getNumber()
{
	if (m_currentEvent != JsonParserEvent::VALUE_NUMBER)
		throw getException("Number", *m_currentEvent);

	return (new JsonNumber(m_tokenizer.asLong())); // TODO might be too tiny
}

JsonBoolean*
JsonParser::getTrue(void)
{
	if (m_currentEvent != JsonParserEvent::VALUE_TRUE)
		throw getException("True", *m_currentEvent);

	return (new JsonBoolean(true));
}

JsonBoolean*
JsonParser::getFalse(void)
{
	if (m_currentEvent != JsonParserEvent::VALUE_FALSE)
		throw getException("False", *m_currentEvent);

	return (new JsonBoolean(false));
}

JsonNull*
JsonParser::getNull(void)
{
	if (m_currentEvent != JsonParserEvent::VALUE_FALSE)
		throw getException("Null", *m_currentEvent);

	return (new JsonNull());
}

JsonValue*
JsonParser::get()
{
	if (JsonParserEvent::START_ARRAY == m_currentEvent)
		return (getArray());
	else if (JsonParserEvent::START_OBJECT == m_currentEvent)
		return (getObject());
	else if (JsonParserEvent::KEY_NAME == m_currentEvent || JsonParserEvent::VALUE_STRING == m_currentEvent)
		return (getString());
	else if (JsonParserEvent::VALUE_NUMBER == m_currentEvent)
	{
		if (m_tokenizer.isDecimal())
			return (getDecimal());

		return (getNumber());
	}
	else if (JsonParserEvent::VALUE_TRUE == m_currentEvent)
		return (getTrue());
	else if (JsonParserEvent::VALUE_FALSE == m_currentEvent)
		return (getFalse());
	else if (JsonParserEvent::VALUE_NULL == m_currentEvent)
		return (getNull());
	else
		throw getException("Unknown Value Type", *m_currentEvent);
}

JsonArray*
JsonParser::getArray(void)
{
	if (m_currentEvent != JsonParserEvent::START_ARRAY)
		throw getException("Array", *m_currentEvent);

	JsonArray *array = new JsonArray();
	try
	{
		while (hasNext())
		{
			JsonParserEvent *event = next();
			if (event == JsonParserEvent::END_ARRAY)
			{
				return array;
			}

			array->add(get());
		}
	}
	catch (...)
	{
		delete array;

		throw;
	}

	throw parsingException(JsonToken::END_OF_FILE, "{, [, String, Number, true, false, null, ]");
}

JsonObject*
JsonParser::getObject(void)
{
	JsonObject *object = new JsonObject();

	try
	{
		while (hasNext())
		{
			JsonParserEvent *event = next();

			if (event == JsonParserEvent::END_OBJECT)
				return (object);

			std::string key = getRawString();

			next();

			object->put(key, get());
		}
	}
	catch (...)
	{
		delete object;

		throw;
	}

	throw parsingException(JsonToken::END_OF_FILE, "String, }");
}

bool
JsonParser::hasNext()
{
	if (m_stack.empty() && (m_currentEvent != NULL && m_currentEvent->compareTo(JsonParserEvent::KEY_NAME) > 0))
	{
		JsonToken *token = m_tokenizer.nextToken();

		if (token != JsonToken::END_OF_FILE)
			throw JsonParseException::expectedEndOfFile(token, m_tokenizer.location());

		return (false);
	}
	else if (!m_stack.empty() && !m_tokenizer.hasNextToken())
	{
		m_currentEvent = m_currentContext->nextEvent(*this, m_tokenizer, m_currentEvent, m_currentContext, m_stack);

		return (false);
	}

	return (true);
}

JsonParserEvent*
JsonParser::next()
{
	if (!hasNext())
		throw new NoSuchElementException();

	return (m_currentEvent = m_currentContext->nextEvent(*this, m_tokenizer, m_currentEvent, m_currentContext, m_stack));
}
