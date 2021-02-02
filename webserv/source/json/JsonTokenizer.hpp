/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonTokenizer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:53:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 18:53:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONTOKENIZER_HPP_
# define JSONTOKENIZER_HPP_

#include <json/JsonLocation.hpp>
#include <json/JsonParseException.hpp>
#include <algorithm>
#include <cctype>
#include <string>

class JsonTokenizer
{
	public:
		typedef std::string::size_type size_type;

	private:
		std::string m_source;
		size_type m_lineNo;
		size_type m_columnNo;
		bool m_minus;
		bool m_dot;
		size_type m_start;
		size_type m_index;

	public:
		JsonTokenizer(void);
		JsonTokenizer(const std::string &source);
		JsonTokenizer(const JsonTokenizer &other);

		JsonTokenizer&
		operator=(const JsonTokenizer &other);

	private:
		inline void
		expectRead(const char *str)
		{
			if (!str)
				return;

			while (*str)
			{
				char c = read();

				if (c != *str)
					throwExpected(*str, c);

				str++;
			}
		}

		void
		readString(void);

		void
		readNumber(char c);

		inline char
		read(void)
		{
			if (m_index == m_source.size())
				return (-1);

			return (m_source[m_index++]);
		}

		inline char
		peek(size_type offset)
		{
			if (m_index + offset == m_source.size())
				return (-1);

			return (m_source[m_index + offset]);
		}

		inline char
		peek(void)
		{
			return (peek(0));
		}

		inline void
		reset()
		{
			m_dot = false;
			m_minus = false;
		}

		inline void
		throwUnexpected(char c)
		{
			throw JsonParseException::unexpectedChar(c, location());
		}

		inline void
		throwExpected(char expected, char got)
		{
			throw JsonParseException::expectedChar(got, expected, location());
		}

	public:
		const JsonToken*
		nextToken(void);

		inline bool
		hasNextToken()
		{
			size_type offset = 0;

			char c = peek(offset);

			while (std::isspace(c))
				c = peek(++offset);

			return (c != -1);
		}

		inline std::string
		asRawString(void) const
		{
			return (m_source.substr(m_start, m_index - m_start));
		}

		inline std::string
		asString(void) const
		{
			/* Remove the " */
			return (m_source.substr(m_start + 1, m_index - m_start - 2));
		}

		long
		asLong(void) const;

		double
		asDouble(void) const;

		inline bool
		isDecimal(void) const
		{
			return (m_dot);
		}

		inline int
		computePrecision() const
		{
			if (!isDecimal())
				return (0);

			return (JsonTokenizer::computePrecision(asRawString()));
		}

		inline JsonLocation
		location()
		{
			return JsonLocation(m_lineNo, m_columnNo, m_index);
		}

		inline std::string
		source()
		{
			return (m_source);
		}

		inline std::string::size_type
		index()
		{
			return (m_index);
		}

		inline std::string::size_type
		start()
		{
			return (m_start);
		}

	public:
		static inline int
		computePrecision(const std::string &str)
		{
			/* length - index of . - 1, take min(x, 10) to avoid underflow, and max(x, 1) to avoid 0 */
			return (std::max(std::min(str.length() - str.find_last_of('.') - 1, std::string::size_type(10)), std::string::size_type(1)));
		}
};

#endif /* JSONTOKENIZER_HPP_ */
