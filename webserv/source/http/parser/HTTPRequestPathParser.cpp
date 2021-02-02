/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestPathParser.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 21:10:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/01 21:10:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/status/HTTPRequestURLTooLongException.hpp>
#include <http/parser/HTTPRequestPathParser.hpp>
#include <io/File.hpp>
#include <unit/DataSize.hpp>
#include <util/Number.hpp>
#include <iostream>

DataSize HTTPRequestPathParser::MAX_LENGTH = DataSize::ofKilobytes(4);

HTTPRequestPathParser::HTTPRequestPathParser() :
		m_state(S_PATH),
		m_path("/"),
		m_original("/"),
		m_queryKey(),
		m_queryValue(),
		m_hexBeforeState(),
		m_hexStorer(),
		m_hex(),
		m_query(),
		m_fragment(),
		m_dot(),
		m_level()
{
	m_path.reserve(60);
	m_original.reserve(60);
}

void
HTTPRequestPathParser::consume(char c)
{
	switch (m_state)
	{
		case S_PATH:
		{
			if (c == ' ')
				m_state = S_END;
			else if (c == '+')
				commitHexToPath(' ');
			else if (c == '%')
				hexStart(&HTTPRequestPathParser::commitHexToPath);
			else if (c == '?')
			{
				m_query.set();
				m_state = S_QUERY_STRING_KEY;
			}
			else if (c == '#')
			{
				m_fragment.set();
				commitQueryKeyValue(S_FRAGMENT);
			}
			else
				commitHexToPath(c);

			break;
		}

		case S_QUERY_STRING_KEY:
		{
			if (c == '=')
				m_state = S_QUERY_STRING_VALUE;
			else if (c == '%')
				hexStart(&HTTPRequestPathParser::commitHexToKey);
			else if (c == '#')
			{
				m_fragment.set();
				commitQueryKeyValue(S_FRAGMENT);
			}
			else if (c == '+')
				commitHexToKey(' ');
			else if (c == ' ')
				commitQueryKeyValue(S_END);
			else
				commitHexToKey(c);

			break;
		}

		case S_QUERY_STRING_VALUE:
		{
			if (c == '%')
				hexStart(&HTTPRequestPathParser::commitHexToValue);
			else if (c == '&')
				commitQueryKeyValue(S_QUERY_STRING_KEY);
			else if (c == '#')
			{
				m_fragment.set();
				commitQueryKeyValue(S_FRAGMENT);
			}
			else if (c == '+')
				commitHexToValue(' ');
			else if (c == ' ')
				commitQueryKeyValue(S_END);
			else
				commitHexToValue(c);

			break;
		}

		case S_FRAGMENT:
		{
			if (c == ' ')
				m_state = S_END;
			else if (c == '%')
				hexStart(&HTTPRequestPathParser::commitHexToFragment);
			else
				commitHexToFragment(c);

			break;
		}

		case S_HEX_START:
		{
			m_hex.clear();
			m_hex += c;

			m_state = S_HEX_END;

			break;
		}

		case S_HEX_END:
		{
			m_hex += c;

			char h = Number::parse<char>(m_hex, Number::HEX);
			if (h == 0)
				throw Exception("Decoded hex value cannot be a null terminator");

			((this)->*(m_hexStorer))(h); /* Function pointer. */
			m_state = m_hexBeforeState;

			break;
		}

		case S_END:
			return;
	}

	m_original += c;

	if (static_cast<long>(m_original.size()) >= MAX_LENGTH.toBytes())
		throw HTTPRequestURLTooLongException();
}

void
HTTPRequestPathParser::reset()
{
	m_state = S_PATH;
	m_path = "/";
	m_original = m_path;
	m_queryKey.clear();
	m_queryValue.clear();
	m_hexBeforeState = S_PATH;
	m_hexStorer = NULL;
	m_hex.clear();
	m_query.unset();
	m_fragment.unset();
	m_dot = 0;
	m_level = 0;
}

void
HTTPRequestPathParser::commitHexToPath(char c)
{
	m_path += c;

	if (c == '/')
	{
		if (m_dot == 2)
		{
			m_path = File(m_path).parent().parent().path();

			if (--m_level == -1)
				throw Exception("Out of root directory");
		}
		else
			m_level++;

		m_dot = 0;
	}
	else if (c == '.')
		m_dot++;
}

void
HTTPRequestPathParser::commitHexToKey(char c)
{
	m_queryKey += c;
}

void
HTTPRequestPathParser::commitHexToValue(char c)
{
	m_queryValue += c;
}

void
HTTPRequestPathParser::commitHexToFragment(char c)
{
	m_fragment.get() += c;
}

void
HTTPRequestPathParser::commitQueryKeyValue(State nextState)
{
	m_query.get()[m_queryKey] = m_queryValue;
	m_queryKey.clear();
	m_queryValue.clear();
	m_state = nextState;
}
