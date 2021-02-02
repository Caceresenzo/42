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
#include <json/JsonParserEvent.hpp>

class JsonToken :
		public Enum<JsonToken>
{
	private:
		std::string m_displayable;
		const JsonParserEvent *m_event;
		bool m_isValue;

	public:
		JsonToken() :
				m_displayable(),
				m_event(NULL),
				m_isValue(false)
		{
		}

		JsonToken(const std::string &displayable, const JsonParserEvent *event, bool isValue) :
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

		inline const JsonParserEvent*
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
		static const JsonToken *CURLYOPEN;
		static const JsonToken *SQUAREOPEN;
		static const JsonToken *COLON;
		static const JsonToken *COMMA;
		static const JsonToken *STRING;
		static const JsonToken *NUMBER;
		static const JsonToken *TRUE;
		static const JsonToken *FALSE;
		static const JsonToken *NULL_; /* Collide with NULL */
		static const JsonToken *CURLYCLOSE;
		static const JsonToken *SQUARECLOSE;
		static const JsonToken *END_OF_FILE;
};

#endif /* JSONTOKEN_HPP_ */
