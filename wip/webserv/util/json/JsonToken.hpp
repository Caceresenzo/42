/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonToken.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:04:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 19:04:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONTOKEN_HPP_
# define JSONTOKEN_HPP_

#include <util/Enum.hpp>
#include <string>
#include <util/json/JsonParserEvent.hpp>

class JsonToken :
		public Enum<JsonToken>
{
	private:
		std::string m_displayable;
		JsonParserEvent *m_event;
		bool m_isValue;

	public:
		JsonToken() :
				m_displayable(),
				m_event(NULL),
				m_isValue(false)
		{
		}

		JsonToken(const std::string &displayable, JsonParserEvent *event, bool isValue) :
				m_displayable(displayable),
				m_event(event),
				m_isValue(isValue)
		{
		}

		JsonToken(const JsonToken &other) :
				m_displayable(other.m_displayable),
				m_event(other.m_event),
				m_isValue(other.m_isValue)
		{
		}

		JsonToken&
		operator =(const JsonToken &other)
		{
			if (this != &other)
			{
				m_displayable = other.m_displayable;
				m_event = other.m_event;
				m_isValue = other.m_isValue;
			}

			return (*this);
		}

		inline const std::string&
		getDisplayable(void) const
		{
			return (m_displayable);
		}

		inline JsonParserEvent*
		getEvent(void) const
		{
			return (m_event);
		}

		inline bool
		isValue(void) const
		{
			return (m_isValue);
		}

	public:
		static JsonToken *CURLYOPEN;
		static JsonToken *SQUAREOPEN;
		static JsonToken *COLON;
		static JsonToken *COMMA;
		static JsonToken *STRING;
		static JsonToken *NUMBER;
		static JsonToken *TRUE;
		static JsonToken *FALSE;
		static JsonToken *NULL_; /* Collide with NULL */
		static JsonToken *CURLYCLOSE;
		static JsonToken *SQUARECLOSE;
		static JsonToken *END_OF_FILE;
};

#endif /* JSONTOKEN_HPP_ */
