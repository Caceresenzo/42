/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeaderFieldsParser.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 21:46:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/01 21:46:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/parser/exception/status/HTTPRequestHeaderTooBigException.hpp>
#include <http/parser/HTTPHeaderFieldsParser.hpp>
#include <unit/DataSize.hpp>

DataSize HTTPHeaderFieldsParser::MAX_SIZE = DataSize::ofKilobytes(8);

HTTPHeaderFieldsParser::HTTPHeaderFieldsParser(bool limited) :
		m_limited(limited),
		m_state(S_FIELD),
		m_headerFields(),
		m_key(),
		m_value(),
		m_consumed(limited)
{
}

void
HTTPHeaderFieldsParser::consume(char c)
{
	switch (m_state)
	{
		case S_FIELD:
		{
			if (c == ' ')
			{
				if (m_key.empty())
					throw Exception("Space before field");
				else
					throw Exception("Space after field");
			}
			else if (c == ':')
				m_state = S_COLON;
			else
				m_key += c;

			break;
		}

		case S_COLON:
		{
			if (c == ' ')
				m_state = S_SPACES_BEFORE_VALUE;
			else
			{
				m_state = S_VALUE;
				m_value += c;
			}

			break;
		}

		case S_SPACES_BEFORE_VALUE:
		{
			if (c != ' ')
			{
				m_state = S_VALUE;
				m_value += c;
			}

			break;
		}

		case S_VALUE:
		{
			if (c == ' ')
				m_state = S_SPACES_AFTER_VALUE;
			else if (c == '\r')
				commit(S_END_R);
			else if (c == '\n')
				commit(S_END_N);
			else
				m_value += c;

			break;
		}

		case S_SPACES_AFTER_VALUE:
		{
			if (c == ' ')
				m_state = S_SPACES_AFTER_VALUE;
			else if (c == '\r')
				commit(S_END_R);
			else if (c == '\n')
				commit(S_END_N);
			else
			{
				m_value += ' ';
				m_value += c;
				m_state = S_VALUE;
			}

			break;
		}

		case S_END_R:
		{
			if (c == '\n')
				m_state = S_END_N;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case S_END_N:
		{
			if (c == '\r')
				m_state = S_END_R2;
			else if (c == '\n')
				m_state = S_END;
			else
			{
				m_key += c;
				m_state = S_FIELD;
			}

			break;
		}

		case S_END_R2:
		{
			if (c == '\n')
				m_state = S_END;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case S_END:
			return;
	}

//	std::cout << m_state;

	if (m_limited && ++m_consumed >= MAX_SIZE.toBytes())
		throw HTTPRequestHeaderTooBigException();
}

void
HTTPHeaderFieldsParser::reset()
{
	m_state = S_FIELD;
	m_headerFields.clear();
	m_key.clear();
	m_value.clear();
	m_consumed = 0;
}

void
HTTPHeaderFieldsParser::commit(State nextState)
{
	m_headerFields.set(m_key, m_value, true);

	m_key.clear();
	m_value.clear();

	m_state = nextState;
}
