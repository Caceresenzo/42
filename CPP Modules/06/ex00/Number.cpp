/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:24:43 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/01 15:24:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Number.hpp"

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

Number::Number() :
		_precision(0), _value(0.0)
{
}

Number::Number(const std::string raw)
{
	this->_precision = -1;
	this->_value = parseDouble(raw, &_precision);
}

Number::~Number()
{
}

Number::Number(const Number &other)
{
	this->operator =(other);
}

Number&
Number::operator=(const Number &other)
{
	if (this != &other)
	{
		this->_precision = other._precision;
		this->_value = other._value;
	}

	return (*this);
}

double
Number::ensureParsing(bool nanIsFailure)
{
	if (_precision == -1 || (nanIsFailure && std::isnan(this->_value)))
		throw Number::NumberException::impossible();

	return (this->_value);
}

char
Number::asChar()
{
	ensureParsing(true);

	if (this->_value < SCHAR_MIN_AS_DOUBLE || this->_value > SCHAR_MAX_AS_DOUBLE)
		throw Number::NumberException::impossible();

	char c = static_cast<char>(_value);

	if (!std::isprint(c))
		throw Number::NumberException::nonDisplayable();

	return (c);
}

int
Number::asInt()
{
	ensureParsing(true);

	if (this->_value < INT_MIN_AS_DOUBLE || this->_value > INT_MAX_AS_DOUBLE)
		throw Number::NumberException::impossible();

	return (static_cast<int>(_value));
}

float
Number::asFloat()
{
	ensureParsing(false);

	if (std::isnan(_value))
		return (nanf(""));

	return (static_cast<float>(_value));
}

double
Number::asDouble()
{
	return (static_cast<double>(ensureParsing(false)));
}

int
Number::precision()
{
	return (this->_precision);
}

double
Number::parseDouble(std::string str, int *precision)
{
	char c;
	const char *cstr = str.c_str();

	size_t index = 0;
	while ((c = cstr[index]) && std::isspace(c))
		index++;

	if (!c)
		throw NumberException::invalidFormat("empty");

	*precision = 1;

	double negativity = 1.0;

	bool sign = false;
	while ((c = cstr[index]) && (c == '+' || c == '-'))
	{
		index++;

		if (sign)
			throw NumberException::invalidFormat("multiple sign", index);

		if ((sign = true) && c == '-')
			negativity = -1.0;
	}

	size_t start = index;

	int isNan = 0;
	if (str.length() == start + 4 && str.substr(start, 4) == "nanf")
		isNan = 2;
	else if (str.length() == start + 3 && str.substr(start, 3) == "nan")
		isNan = 1;

	if (isNan)
	{
		if (sign)
		{
			if (isNan == 1)
				throw NumberException::invalidFormat("'signed' nan", index);
			throw NumberException::invalidFormat("'signed' nanf", index);
		}

		return (nan(""));
	}

	bool isInf = false;
	if (str.length() == start + 4 && str.substr(start, 4) == "inff")
		isInf = true;
	else if (str.length() == start + 3 && str.substr(start, 3) == "inf")
		isInf = true;

	if (!isInf)
	{
		if (str.length() == start + 1 && !std::isdigit((c = cstr[start])))
		{
			if (!std::isprint(c))
				throw NumberException::invalidFormat("non displayable", index);
			return (static_cast<double>(c));
		}

		std::string preComma = std::string("0");
		std::string postComma = std::string("0");

		if ((c = cstr[index]) != '.')
		{
			if (!std::isdigit(cstr[index]))
				throw NumberException::invalidFormat("no number (near '" + std::string(cstr + index) + "')", index);

			while ((c = cstr[index]) && std::isdigit(c))
				index++;

			preComma = str.substr(start, index - start);
		}

		if (c == '.')
		{
			size_t comma = ++index;
			while ((c = cstr[index]) && std::isdigit(c))
				index++;

			if (comma != index)
				postComma = str.substr(comma, index - comma);
		}

		if (c && (c != 'f' || cstr[index + 1]))
			throw NumberException::invalidFormat("unexpected content after number (near '" + std::string(cstr + index) + "')", index);

		*precision = postComma.length();

		try {
			return (atof((preComma + "." + postComma).c_str()) * negativity);
		} catch (std::out_of_range &e) {
		}
	}

	return (negativity / 0.0); /* Infinity */
}

bool
Number::dump(std::string str)
{
	try {
		Number::dump(Number(str));

		return (true);
	} catch (Number::NumberException &e) {
		std::cerr << COLOR_FAILED "error: " << e.what() << COLOR_RESET << std::endl;

		if (e.position() != std::string::npos)
		{
			std::cerr << str << std::endl;

			std::cerr << COLOR_TYPES;

			for (size_t index = 0; index < e.position(); index++)
				std::cerr << " ";

			std::cerr << "^" COLOR_RESET << std::endl;
		}

		return (false);
	}
}

void
Number::dump(Number number)
{
	std::cout << COLOR_TYPES "char" COLOR_RESET ": ";

	try
	{
		char c = number.asChar();

		std::cout << '\'' << COLOR_NUMBER << c << COLOR_RESET << '\'';
	}
	catch (std::exception &e)
	{
		std::cout << COLOR_FAILED << e.what();
	}

	std::cout << COLOR_RESET << std::endl;
	std::cout << COLOR_TYPES "int" COLOR_RESET ": ";

	try
	{
		std::cout << COLOR_NUMBER << number.asInt();
	}
	catch (std::exception &e)
	{
		std::cout << COLOR_FAILED << e.what();
	}

	std::cout << COLOR_RESET << std::endl;
	std::cout << COLOR_TYPES "float" COLOR_RESET ": ";

	try
	{
		std::cout << COLOR_NUMBER << std::fixed << std::setprecision(number._precision) << number.asFloat() << 'f';
	}
	catch (std::exception &e)
	{
		std::cout << COLOR_FAILED << e.what();
	}

	std::cout << COLOR_RESET << std::endl;
	std::cout << COLOR_TYPES "double" COLOR_RESET ": ";

	try
	{
		std::cout << COLOR_NUMBER << std::fixed << std::setprecision(number._precision) << number.asDouble();
	}
	catch (std::exception &e)
	{
		std::cout << COLOR_FAILED << e.what();
	}

	std::cout << COLOR_RESET << std::endl;
}

Number::NumberException::NumberException(void) :
		std::exception(), _message("no message"), _position(std::string::npos)
{
}

Number::NumberException::NumberException(std::string message) :
		std::exception(), _message(message), _position(std::string::npos)
{
}

Number::NumberException::NumberException(std::string message, size_t position) :
		std::exception(), _message(message), _position(position)
{
}

Number::NumberException::NumberException(const NumberException &other) :
		std::exception(), _message(other._message), _position(other._position)
{
}

Number::NumberException::~NumberException(void) throw ()
{
}

Number::NumberException&
Number::NumberException::operator =(const NumberException &other)
{
	(void)other;

	return (*this);
}

const char*
Number::NumberException::what() const throw ()
{
	return (this->_message.c_str());
}

const std::string&
Number::NumberException::message() const
{
	return (this->_message);
}

const size_t&
Number::NumberException::position() const
{
	return (this->_position);
}

Number::NumberException
Number::NumberException::invalidFormat(std::string reason)
{
	return (NumberException("invalid format: " + reason));
}

Number::NumberException
Number::NumberException::invalidFormat(std::string reason, size_t position)
{
	return (NumberException("invalid format: " + reason, position));
}

Number::NumberException
Number::NumberException::impossible()
{
	return (NumberException("impossible"));
}

Number::NumberException
Number::NumberException::nonDisplayable()
{
	return (NumberException("Non displayable"));
}
