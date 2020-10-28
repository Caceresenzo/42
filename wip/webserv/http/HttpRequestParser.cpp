/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:29:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 17:29:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_ctype.h>
#include <exception/Exception.hpp>
#include <http/HttpRequestParser.hpp>
#include <string>

HttpRequestParser::HttpRequestParser() :
		m_state(S_NOT_STARTED),
		m_method(),
		m_path(),
		m_major(-1),
		m_minor(-1),
		m_last_char(0),
		m_last_char2(0)
{
	m_method.reserve(16);
	m_path.reserve(60);
}

void
HttpRequestParser::consume(char c)
{
	switch (m_state)
	{
		case S_NOT_STARTED:
		case S_METHOD:
		{
			if (c == ' ')
			{
				if (m_state == S_NOT_STARTED)
					throw Exception("No method: ");

				m_state = S_SPACES_BEFORE_PATH;
			}
			else
			{
				m_state = S_METHOD;
				m_method += c;
			}

			break;
		}

		case S_SPACES_BEFORE_PATH:
		{
			if (c != ' ')
			{
				if (c != '/')
					throw Exception("No slash");

				m_state = S_PATH;
				m_path += '/';
			}

			break;
		}

		case S_PATH:
		{
			if (c == ' ')
				m_state = S_HTTP_START;
			else
				m_path += c;

			break;
		}

		case S_HTTP_START:
		{
			if (c != 'H')
				throw Exception("Expected `H`");

			m_state = S_HTTP_H;

			break;
		}

		case S_HTTP_H:
		{
			if (c != 'T')
				throw Exception("Expected `T`");

			m_state = S_HTTP_HT;

			break;
		}

		case S_HTTP_HT:
		{
			if (c != 'T')
				throw Exception("Expected `T`");

			m_state = S_HTTP_HTT;

			break;
		}

		case S_HTTP_HTT:
		{
			if (c != 'P')
				throw Exception("Expected `P`");

			m_state = S_HTTP_HTTP;

			break;
		}

		case S_HTTP_HTTP:
		{
			if (c != '/')
				throw Exception("Expected `/`");

			m_state = S_HTTP_SLASH;

			break;
		}

		case S_HTTP_SLASH:
		{
			if (!::isdigit(c))
				throw Exception("Expected a number");

			m_major = c - '0';
			m_state = S_HTTP_MAJOR;

			break;
		}

		case S_HTTP_MAJOR:
		{
			if (c != '.')
				throw Exception("Expected `.`");

			m_state = S_HTTP_DOT;

			break;
		}

		case S_HTTP_DOT:
		{
			if (!::isdigit(c))
				throw Exception("Expected a number");

			m_minor = c - '0';
			m_state = S_HTTP_MINOR;

			break;
		}

		case S_HTTP_MINOR:
		{
			if (c == '\r')
				m_state = S_HTTP_END;
			else if (c == '\n')
				m_state = S_HTTP_END2;
			else
				throw Exception("Expected a \\r or \\n");

			break;
		}

		case S_HTTP_END:
		{
			if (c == '\n')
				m_state = S_HTTP_END2;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case S_HTTP_END2:
		{
			m_state = S_FIELD;

			break;
		}

		case S_FIELD:
		{
			if (m_last_char2 == '\n' && m_last_char == '\r' && c == '\n')
				m_state = S_END;

			break;
		}
	}

	m_last_char2 = m_last_char;
	m_last_char = c;
}

HttpRequestParser::State
HttpRequestParser::state() const
{
	return (m_state);
}

std::string
HttpRequestParser::method() const
{
	return (m_method);
}

std::string
HttpRequestParser::path() const
{
	return (m_path);
}

int
HttpRequestParser::major() const
{
	return (m_major);
}

int
HttpRequestParser::minor() const
{
	return (m_minor);
}
