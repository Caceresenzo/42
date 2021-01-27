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
#include <json/JsonLocation.hpp>
#include <json/JsonParseException.hpp>
#include <json/JsonParserEvent.hpp>
#include <json/JsonTokenizer.hpp>
#include <json/JsonValue.hpp>
#include <json/JsonArray.hpp>
#include <json/JsonBoolean.hpp>
#include <json/JsonDecimal.hpp>
#include <json/JsonNull.hpp>
#include <json/JsonNumber.hpp>
#include <json/JsonObject.hpp>
#include <json/JsonString.hpp>
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

				virtual const JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, const JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack) = 0;
		};

		class NoneContext :
				public Context
		{
			public:
				const JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, const JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack);
		};

		class ObjectContext :
				public Context
		{
			private:
				bool m_firstValue;

			public:
				ObjectContext();

				const JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, const JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack);
		};

		class ArrayContext :
				public Context
		{
			private:
				bool m_firstValue;

			public:
				ArrayContext();

				const JsonParserEvent*
				nextEvent(JsonParser &parser, JsonTokenizer &tokenizer, const JsonParserEvent *&currentEvent, Context *&currentContext, std::stack<Context*> &stack);
		};

	private:
		Context *m_currentContext;
		const JsonParserEvent *m_currentEvent;

		std::stack<Context*> m_stack;
		JsonTokenizer m_tokenizer;

	public:
		JsonParser(const std::string &source);
		~JsonParser(void);

	protected:
		JsonParseException
		parsingException(const JsonToken *token, const std::string &expectedTokens)
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

		const JsonParserEvent*
		next();

		JsonValue*
		get();
};

#endif /* JSONPARSER_HPP_ */
