/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:04:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:04:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <exception/IllegalStateException.hpp>
#include <util/Enum.hpp>
#include <util/json/JsonLocation.hpp>
#include <util/json/JsonParseException.hpp>
#include <util/json/JsonParserEvent.hpp>
#include <util/json/JsonTokenizer.hpp>
#include <util/json/JsonValue.hpp>
#include <util/json/JsonArray.hpp>
#include <util/json/JsonBoolean.hpp>
#include <util/json/JsonDecimal.hpp>
#include <util/json/JsonNull.hpp>
#include <util/json/JsonNumber.hpp>
#include <util/json/JsonObject.hpp>
#include <util/json/JsonString.hpp>
#include <stack>
#include <string>

class JsonParser
{
	private:
		class Context
		{
			public:

				virtual
				~Context()
				{
				}

				virtual JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack) = 0;
		};

		class NoneContext :
				public Context
		{
			public:
				JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack);
		};

		class ObjectContext :
				public Context
		{
			private:
				bool m_firstValue;

			public:
				ObjectContext();

				JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack);
		};

		class ArrayContext :
				public Context
		{
			private:
				bool m_firstValue;

			public:
				ArrayContext();

				JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack);
		};

	private:
		Context *m_currentContext;
		JsonParserEvent *m_currentEvent;

		std::stack<Context*> m_stack;
		JsonTokenizer m_tokenizer;

	public:
		JsonParser(const std::string &source);
		~JsonParser(void);

	protected:
		JsonParseException
		parsingException(JsonToken *token, const std::string &expectedTokens)
		{
			return (JsonParseException::parsing(token, expectedTokens, m_tokenizer.location()));
		}

		IllegalStateException
		getException(const std::string &message, const JsonParserEvent &event)
		{
			return (IllegalStateException("Cannot get `" + message + "` here, got event: " + event.name()));
		}

	public:
		std::string
		getRawString();

		JsonString*
		getString();

		JsonDecimal*
		getDecimal();

		JsonNumber*
		getNumber();

		JsonBoolean*
		getTrue(void);

		JsonBoolean*
		getFalse(void);

		JsonNull*
		getNull(void);

		JsonArray*
		getArray(void);

		JsonObject*
		getObject(void);

		bool
		hasNext();

		JsonParserEvent*
		next();

		JsonValue*
		get();
};

#endif /* JSONPARSER_HPP_ */
