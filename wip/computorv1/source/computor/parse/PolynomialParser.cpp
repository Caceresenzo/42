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

PolynomialParser::PolynomialParser(const StringReader &reader) :
		m_reader(reader),
		m_values(),
		m_state(START),
		m_number_value(),
		m_exponent_value()
{
}

PolynomialParser::polynomial_type::map
PolynomialParser::parse(void)
{
	while (!m_reader.is_end_of_content())
	{
		consume();
	}

	while (!consume())
		;

	return (m_values);
}

bool
PolynomialParser::consume()
{
#if defined(DEBUG) && DEBUG
	try
	{
		char chr = m_reader.peek();
		std::string chr_string = "\\0";
		if (chr)
			chr_string = chr;

		std::cout << "state=" << std::left << std::setw(10) << to_string(m_state) << std::setw(0) << "  chr=" << chr_string << std::endl;

		return (do_consume());
	}
	catch (...)
	{
		std::cout << "error=" << std::left << std::setw(10) << to_string(m_state) << std::setw(0) << std::endl;
		throw;
	}
#else
	return (do_consume());
#endif
}

bool
PolynomialParser::do_consume()
{
	m_reader.skip_whitespaces();

	switch (m_state)
	{
		case START:
		{
			reset();

			char chr = m_reader.peek();

			if (is_minus(chr) || Character::is_digit(chr))
			{
				m_state = NUMBER;
				return (false);
			}

			if (is_variable(chr))
			{
				m_state = VARIABLE;
				return (false);
			}

			if (is_sign(chr))
			{
				m_state = NUMBER;
				return (false);
			}

			return (expected("minus, number, variable"));
		}

		case NUMBER:
		{
			commit_number();

			char chr = m_reader.skip_whitespaces().peek();

			if (is_multiply(chr))
			{
				m_state = MULTIPLY;
				return (false);
			}

			if (is_variable(chr))
			{
				m_state = VARIABLE;
				return (false);
			}

			if (is_sign(chr))
			{
				commit();
				m_state = START;
				return (false);
			}

			if (is_end(chr))
			{
				m_state = END;
				return (false);
			}

			return (expected("multiply, variable, sign, end"));
		}

		case MULTIPLY:
		{
			char chr = m_reader.read();

			if (is_multiply(chr) || is_variable(chr))
			{
				m_state = VARIABLE;
				return (false);
			}

			return (expected("multiply, variable"));
		}

		case VARIABLE:
		{
			char chr = m_reader.read();

			if (is_variable(chr))
			{
				m_state = CIRCUMFLEX;
				return (false);
			}

			return (expected("variable"));
		}

		case CIRCUMFLEX:
		{
			char chr = m_reader.read();

			if (is_circumflex(chr))
			{
				m_state = POWER;
				return (false);
			}

			return (expected("circumflex"));
		}

			/* chr = "0123456789" */
		case POWER:
		{
			commit_power();

			char chr = m_reader.skip_whitespaces().peek();

			if (is_sign(chr))
			{
				commit();
				m_state = START;
				return (false);
			}

			if (is_end(chr))
			{
				m_state = END;
				return (false);
			}

			return (expected("number, sign, end"));
		}

		case END:
		{
			commit();
			return (true);
		}
	}

	throw ParseException("unhandled state", m_reader);
}

bool
PolynomialParser::expected(const std::string &expectations)
{
	throw ParseException("expected: " + expectations, m_reader);
	return (false);
}

bool
PolynomialParser::unexpected()
{
	throw ParseException("unexpected", m_reader);
	return (false);
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
PolynomialParser::is_dot(char chr)
{
	return (chr == '.');
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
	return (chr == StringReader::END_OF_CONTENT);
}

void
PolynomialParser::consume_number(bool is_floating, void *out)
{
	bool negative = false;

	m_reader.skip_whitespaces();

	char chr = m_reader.peek();
	if (is_sign(chr))
	{
		m_reader.skip().skip_whitespaces();

		negative = is_minus(chr);
	}

	std::string accumulator;
	bool dot = false;

	do
	{
		chr = m_reader.peek();
		if (Character::is_digit(chr))
		{
			accumulator += chr;
		}
		else if (is_dot(chr) && !dot)
		{
			accumulator += chr;
			dot = true;
		}
		else
			break;

		m_reader.skip();
	}
	while (!m_reader.is_end_of_content());

	if (accumulator.empty())
		throw ParseException("number is empty", m_reader);

	if (negative)
		accumulator.insert(accumulator.begin(), '-');

	char *extra = NULL;

	errno = 0;

	if (is_floating)
	{
		long double value = std::strtold(accumulator.c_str(), &extra);
		*(long double*)out = value;
	}
	else
	{
		int value = std::strtol(accumulator.c_str(), &extra, 10);
		*(int*)out = value;
	}

	if (errno)
		throw ParseException("cannot parse number: " + std::string(std::strerror(errno)), m_reader);

	if (extra && extra[0])
		throw ParseException("character in number", m_reader);
}

void
PolynomialParser::commit(void)
{
	if (m_number_value.is_absent() && m_exponent_value.is_absent())
		throw ParseException("no number or exponent", m_reader);

	int exponent = m_exponent_value.or_else(0);
	long double number = m_number_value.or_else(0);

#if defined(DEBUG) && DEBUG
	std::cout << "commit exponent=" << exponent << " " << "number=" << number << std::endl;
#endif

	m_values[exponent] += number;
}

void
PolynomialParser::commit_number(void)
{
	if (m_number_value.is_present())
		throw ParseException("double number commit", m_reader);

	long double value = 0;
	consume_number(true, &value);

	m_number_value.set(value);

#if defined(DEBUG) && DEBUG
	std::cout << "commit=number" << std::endl;
#endif
}

void
PolynomialParser::commit_power(void)
{
	if (m_exponent_value.is_present())
		throw ParseException("double exponent commit", m_reader);

	int value = 0;
	consume_number(false, &value);

	m_exponent_value.set(value);

#if defined(DEBUG) && DEBUG
	std::cout << "commit=power" << std::endl;
#endif
}

void
PolynomialParser::reset(void)
{
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
	StringReader reader(input, start, end);
	PolynomialParser parser(reader);

	parser.parse();

	return (polynomial_type(parser.m_values));
}
