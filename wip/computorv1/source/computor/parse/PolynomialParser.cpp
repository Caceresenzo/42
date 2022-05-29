/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolynomialParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:56:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 22:56:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/parse/ParseException.hpp>
#include <computor/parse/PolynomialParser.hpp>
#include <core/lang/Character.hpp>
#include <core/util/Optional.hpp>
#include <sys/errno.h>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>

PolynomialParser::PolynomialParser(void) :
		m_values(),
		m_state(START),
		m_negate(false),
		m_number(),
		m_number_value(),
		m_exponent_value()
{
}

bool
PolynomialParser::consume(char chr, std::string::size_type index)
{
#if defined(DEBUG) && DEBUG
	try
	{
		std::string chr_string = "\\0";
		if (chr)
			chr_string = chr;

		std::cout << "consume=before  state=" << std::left << std::setw(10) << to_string(m_state) << std::setw(0) << "  chr=" << chr_string << std::endl;

		bool consumed = do_consume(chr, index);

		std::cout << "consume=after   state=" << std::left << std::setw(10) << to_string(m_state) << std::setw(0) << "  consumed=" << consumed << std::endl;

		return (consumed);
	}
	catch (...)
	{
		std::cout << "consume=error   state=" << std::left << std::setw(10) << to_string(m_state) << std::setw(0) << std::endl;
		throw;
	}
#else
	return (do_consume(chr, index));
#endif
}

bool
PolynomialParser::do_consume(char chr, std::string::size_type index)
{
	if (std::isspace(chr))
		return (true);

	switch (m_state)
	{
		case START:
		{
			reset();

			if (is_minus(chr))
			{
				m_state = NEGATE;
				m_negate = true;
				return (true);
			}

			if (Character::is_digit(chr))
			{
				m_state = NUMBER;
				m_number += chr;
				return (true);
			}

			if (is_variable(chr))
			{
				m_state = CIRCUMFLEX;
				return (true);
			}

			return (expected("minus, number, variable", index));
		}

		case NEGATE:
		{
			if (Character::is_digit(chr))
			{
				m_state = NUMBER;
				m_number += chr;
				return (true);
			}

			return (expected("number", index));
		}

		case NUMBER:
		{
			if (Character::is_digit(chr))
			{
				m_number += chr;
				return (true);
			}

			commit_number(index);

			if (is_multiply(chr))
			{
				m_state = MULTIPLY;
				return (true);
			}

			if (is_variable(chr))
			{
				m_state = VARIABLE;
				return (true);
			}

			if (is_end(chr))
			{
				m_state = END;
				return (false);
			}

			return (expected("number, multiply, variable, end", index));
		}

		case MULTIPLY:
		{
			if (is_variable(chr))
			{
				m_state = VARIABLE;
				return (true);
			}

			return (expected("variable", index));
		}

		case VARIABLE:
		{
			if (is_circumflex(chr))
			{
				m_state = CIRCUMFLEX;
				return (true);
			}

			return (expected("circumflex", index));
		}

		case CIRCUMFLEX:
		{
			if (Character::is_digit(chr))
			{
				m_number += chr;
				m_state = POWER;
				return (true);
			}

			return (expected("number", index));
		}

		case POWER:
		{
			if (Character::is_digit(chr))
			{
				m_number += chr;
				return (true);
			}

			if (is_sign(chr))
			{
				commit_power(index);
				commit(index);
				m_state = START;
				return (is_plus(chr));
			}

			if (is_end(chr))
			{
				commit_power(index);
				m_state = END;
				return (false);
			}

			return (expected("number, sign, end", index));
		}

		case END:
		{
			commit(index);
			return (true);
		}
	}

	throw ParseException("unhandled state", index);
}

bool
PolynomialParser::expected(const std::string &expectations, std::string::size_type index)
{
	throw ParseException("expected: " + expectations, index);
	return (false);
}

bool
PolynomialParser::unexpected(std::string::size_type index)
{
	throw ParseException("unexpected", index);
	return (false);
}

void
PolynomialParser::ensure_number_not_empty(std::string::size_type index)
{
	if (m_number.empty())
		throw ParseException("number is empty", index);
}

bool
PolynomialParser::is_variable(char chr)
{
	return (Character::to_uppercase(chr) == 'X');
}

bool
PolynomialParser::is_multiply(char chr)
{
	return (chr == '*');
}

bool
PolynomialParser::is_circumflex(char chr)
{
	return (chr == '^');
}

bool
PolynomialParser::is_sign(char chr)
{
	return (is_minus(chr) || is_plus(chr));
}

bool
PolynomialParser::is_minus(char chr)
{
	return (chr == '-');
}

bool
PolynomialParser::is_plus(char chr)
{
	return (chr == '+');
}

bool
PolynomialParser::is_end(char chr)
{
	return (chr == '\0');
}

void
PolynomialParser::commit(std::string::size_type next_index)
{
	if (m_number_value.is_absent() && m_exponent_value.is_absent())
		throw ParseException("no number or exponent", next_index - 1);

	int exponent = m_exponent_value.or_else(0);
	long double number = m_number_value.or_else(0);

#if defined(DEBUG) && DEBUG
	std::cout << "exponent=" << exponent << " " << "number=" << number << std::endl;
#endif

	if (number == 0)
		return;

	m_values[exponent] = number;
}

void
PolynomialParser::commit_number(std::string::size_type next_index)
{
	if (m_number_value.is_present())
		throw ParseException("double number commit", next_index - 1);

	ensure_number_not_empty(next_index);

	char *extra = NULL;

	errno = 0;
	long double value = std::strtold(m_number.c_str(), &extra);

	if (errno)
		throw ParseException("cannot parse number: " + std::string(std::strerror(errno)), next_index - 1);

	if (extra && extra[0])
		throw ParseException("character in number", next_index - 1);

	m_number_value.set(value);
	m_number.clear();
}

void
PolynomialParser::commit_power(std::string::size_type next_index)
{
	if (m_exponent_value.is_present())
		throw ParseException("double exponent commit", next_index - 1);

	ensure_number_not_empty(next_index);

	char *extra = NULL;

	errno = 0;
	int value = std::strtol(m_number.c_str(), &extra, 10);

	if (errno)
		throw ParseException("cannot parse exponent: " + std::string(std::strerror(errno)), next_index - 1);

	if (extra && extra[0])
		throw ParseException("character in exponent", next_index - 1);

	if (m_negate)
		value *= -1;

	m_exponent_value.set(value);
	m_number.clear();
}

void
PolynomialParser::reset(void)
{
	m_number.clear();
	m_negate = false;
	m_number_value.clear();
	m_exponent_value.clear();
}

std::string
PolynomialParser::to_string(State state)
{
	switch (state)
	{
		case START:
			return ("START");

		case NEGATE:
			return ("NEGATE");

		case NUMBER:
			return ("NUMBER");

		case MULTIPLY:
			return ("MULTIPLY");

		case VARIABLE:
			return ("VARIABLE");

		case CIRCUMFLEX:
			return ("CIRCUMFLEX");

		case POWER:
			return ("POWER");

		case END:
			return ("END");
	}

	return ("UNKNOWN");
}

PolynomialParser::polynomial_type
PolynomialParser::parse(const std::string &input, std::string::size_type start, std::string::size_type end)
{
	PolynomialParser parser;

	std::string::size_type index = start;
	while (index < end)
	{
		char chr = input[index];

		bool consumed = parser.consume(chr, index);
		if (consumed)
			++index;
	}

	bool consumed;
	do
	{
		consumed = parser.consume('\0', index);
	}
	while (!consumed);

	return (polynomial_type(parser.m_values));
}
