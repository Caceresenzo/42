/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:37:54 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 18:37:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

#include <algorithm>
#include <exception>
#include <iostream>

Span::Span() :
        _n(0)
{
}

Span::Span(unsigned int n) :
        _n(n)
{
}

Span::Span(const Span &other) :
        _n(other._n)
{
	this->operator =(other);
}

Span::~Span()
{
}

Span&
Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_n = other._n;
		this->_vector = other._vector;
	}

	return (*this);
}

void
Span::addNumber(int number)
{
	if (this->_vector.size() >= this->_n)
		throw SpanException::capacityReached();

	this->_vector.push_back(number);
}

void
Span::addNumber(std::vector<int> const &numbers)
{
	if (numbers.empty())
		return;

	if (this->_vector.size() + numbers.size() > this->_n)
		throw SpanException::capacityReached();

	this->_vector.insert(this->_vector.end(), numbers.begin(), numbers.end());
}

void
Span::addNumber(int from, int to)
{
	if (from > to)
		throw SpanException::illegalArgument();

	int diff = to - from;

	if (this->_vector.size() + diff > this->_n)
		throw SpanException::capacityReached();

	for (int index = from; index < to; ++index)
		this->_vector.push_back(index);
}

void
Span::addNumber(Span const &other)
{
	addNumber(other._vector);
}

int
Span::shortestSpan() const
{
	if (this->_vector.size() <= 1)
		throw SpanException::requireAtLeast2();

	std::vector<int> copy = std::vector<int>(this->_vector);
	std::sort(copy.begin(), copy.end());

	int shortest = -1;

	for (unsigned int index = 0; index < this->_vector.size() - 1; ++index)
	{
		int diff = std::abs(_vector[index] - _vector[index + 1]);

		if (shortest == -1 || diff < shortest)
			shortest = diff;
	}

	return (shortest);
}

int
Span::longestSpan() const
{
	if (this->_vector.size() <= 1)
		throw SpanException::requireAtLeast2();

	int max = *std::max_element(this->_vector.begin(), this->_vector.end());
	int min = *std::min_element(this->_vector.begin(), this->_vector.end());

	return (max - min);
}

Span::SpanException::SpanException(void) :
        std::exception(),
        _message("no message")
{
}

Span::SpanException::SpanException(std::string message) :
        std::exception(),
        _message(message)
{
}

Span::SpanException::SpanException(const SpanException &other) :
        std::exception(),
        _message(other._message)
{
}

Span::SpanException::~SpanException(void) throw ()
{
}

Span::SpanException&
Span::SpanException::operator =(const SpanException &other)
{
	(void)other;

	return (*this);
}

const char*
Span::SpanException::what() const throw ()
{
	return (this->_message.c_str());
}

const std::string&
Span::SpanException::message() const
{
	return (this->_message);
}

Span::SpanException
Span::SpanException::illegalArgument()
{
	return (SpanException("illegal arguments: from > to"));
}

Span::SpanException
Span::SpanException::capacityReached()
{
	return (SpanException("capacity reached"));
}

Span::SpanException
Span::SpanException::requireAtLeast2()
{
	return (SpanException("require at least to have two number"));
}

void
Span::dump()
{
	for (unsigned int index = 0; index < this->_vector.size(); ++index)
		std::cout << _vector[index] << (index < this->_vector.size() - 1 ? ", " : "");

	std::cout << std::endl;
}
