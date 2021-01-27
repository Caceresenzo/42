/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestParser.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:29:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:32:29 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/BaseBuffer.hpp>
#include <buffer/impl/SocketBuffer.hpp>
#include <http/body/encoding/HTTPBodyEncoding.hpp>
#include <http/body/encoding/IHTTPBodyDecoder.hpp>
#include <http/HTTPClient.hpp>
#include <http/parser/exception/status/HTTPRequestPayloadTooLargeException.hpp>
#include <http/parser/exception/version/UnsupportedHTTPVersion.hpp>
#include <http/parser/HTTPRequestParser.hpp>
#include <libs/ft.hpp>
#include <stddef.h>
#include <util/helper/DeleteHelper.hpp>
#include <util/Optional.hpp>

class HTTPClient;

#if 1
#include <util/URL.hpp> /* Eclipse does not import it. */
#endif

HTTPRequestParser::HTTPRequestParser(HTTPClient &client) :
		m_state(S_NOT_STARTED),
		m_method(),
		m_major(),
		m_minor(),
		m_client(client),
		m_bodyDecoder(),
		m_maxBodySize(-1),
		m_totalSize(0),
		m_max(false)
{
	m_method.reserve(16);
}

HTTPRequestParser::~HTTPRequestParser()
{
	if (m_bodyDecoder)
		m_bodyDecoder->cleanup();
}

void
HTTPRequestParser::consume(char c)
{
	switch (m_state)
	{
		case S_NOT_STARTED:
		{
			if (c == '\r'|| c == '\n')
				break;
			else
				m_state = S_METHOD;
		}
		
		case S_METHOD:
		{
			m_max = false;
			if (c == ' ')
			{
				if (m_state == S_NOT_STARTED)
					throw Exception("No method");

				m_state = S_SPACES_BEFORE_PATH;
			}
			else
			{
				if (!ft::isupper(c))
					throw Exception("Method is only upper-case letter");

				if (m_method.length() > 20)
					throw Exception("Method is over 20 characters");

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
			}

			break;
		}

		case S_PATH:
		{
			m_pathParser.consume(c);

			if (m_pathParser.state() == HTTPRequestPathParser::S_END)
				m_state = S_HTTP_START;

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
			if (!ft::isdigit(c))
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
			if (!ft::isdigit(c))
				throw Exception("Expected a number");

			m_minor = c - '0';
			m_state = S_HTTP_MINOR;

			break;
		}

		case S_HTTP_MINOR:
		{
			if (!HTTPVersion::isSupported(m_minor, m_major))
				throw UnsupportedHTTPVersion::of(m_minor, m_major);

			if (c == '\r')
				m_state = S_HTTP_END_R;
			else if (c == '\n')
				m_state = S_HTTP_END_N;
			else
				throw Exception("Expected a \\r or \\n");

			break;
		}

		case S_HTTP_END_R:
		{
			if (c == '\n')
				m_state = S_HTTP_END_N;
			else
				throw Exception("Expected a \\n");

			break;
		}

		case S_HTTP_END_N:
		{
			if (c == '\r')
				m_state = S_END_R;
			else if (c == '\n')
				m_state = S_END;
			else
			{
				m_state = S_HEADER_FIELDS;
				m_headerFieldsParser.consume(c);
			}

			break;
		}

		case S_END_R:
		{
			if (c == '\n')
				m_state = S_END;
			else
				m_state = S_END;
				
			break;
		}

		case S_HEADER_FIELDS:
		{
			m_headerFieldsParser.consume(c);

			if (m_headerFieldsParser.state() == HTTPHeaderFieldsParser::S_END)
				m_state = S_END;

			break;
		}

		case S_BODY:
			m_state = S_BODY_DECODE;
			m_bodyDecoder = HTTPBodyEncoding::decoderFor(m_headerFieldsParser.headerFields());

			if (m_bodyDecoder == NULL)
			{
				m_state = S_END;
				break;
			}

			if (c == 0)
				break;

		//	__attribute__ ((fallthrough));

		case S_BODY_DECODE:
		{
			size_t consumed = 0;
			bool finished = m_bodyDecoder->consume(m_client.in().storage(), m_client.body(), consumed, m_max);
		
			m_client.in().skip(consumed);
			m_totalSize += consumed;
			
			if (m_maxBodySize != -1 && (long long)m_client.body().size() > m_maxBodySize)
			{
				m_max = true; 
				if (finished)
					throw HTTPRequestPayloadTooLargeException();
			}
		
			if (finished)
				m_state = S_END;

			break;
		}

		case S_END:
			break;

	}
}

void
HTTPRequestParser::reset()
{
	m_state = S_NOT_STARTED;
	m_method.clear();
	m_major = 0;
	m_minor = 0;
	DeleteHelper::pointer(m_bodyDecoder);
	m_maxBodySize = -1;
	m_totalSize = 0;

	m_pathParser.reset();
	m_headerFieldsParser.reset();
}

HTTPRequestParser::State&
HTTPRequestParser::state()
{
	return (m_state);
}

HTTPRequestParser::State
HTTPRequestParser::state() const
{
	return (m_state);
}

std::string
HTTPRequestParser::method() const
{
	return (m_method);
}

void
HTTPRequestParser::maxBodySize(long long maxBodySize)
{
	m_maxBodySize = maxBodySize;
}

const std::string&
HTTPRequestParser::body() const
{
	return (m_client.body());
}

URL
HTTPRequestParser::url()
{
	return (URL(m_pathParser.path(), m_pathParser.query(), m_pathParser.fragment()));
}
