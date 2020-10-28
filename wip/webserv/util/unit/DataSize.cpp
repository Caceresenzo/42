/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataSize.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:37:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:37:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <_ctype.h>
#include <exception/IllegalArgumentException.hpp>
#include <stddef.h>
#include <util/unit/DataSize.hpp>
#include <iostream>
#include <sstream>

DataSize::DataSize(void) :
		m_bytes(0)
{
}

DataSize::DataSize(long long bytes) :
		m_bytes(bytes)
{
}

DataSize::DataSize(const DataSize &other) :
		m_bytes(other.m_bytes)
{
}

DataSize::~DataSize()
{
}

DataSize&
DataSize::operator=(const DataSize &other)
{
	if (this != &other)
		m_bytes = other.m_bytes;

	return (*this);
}

long long
DataSize::toBytes() const
{
	return (m_bytes);
}

DataSize
DataSize::ofBytes(long bytes)
{
	return DataSize(bytes);
}

DataSize
DataSize::ofKilobytes(long kilobytes)
{
	return DataSize(kilobytes * BYTES_PER_KB);
}

DataSize
DataSize::ofMegabytes(long megabytes)
{
	return DataSize(megabytes * BYTES_PER_KB);
}

DataSize
DataSize::ofGigabytes(long gigabytes)
{
	return DataSize(gigabytes * BYTES_PER_KB);
}

DataSize
DataSize::ofTerabytes(long terabytes)
{
	return DataSize(terabytes * BYTES_PER_KB);
}

DataSize
DataSize::of(long amount, const DataUnit &unit)
{
	return DataSize(amount * unit.size().toBytes());
}

DataSize
DataSize::parse(const std::string &text)
{
	return (parse(text, *DataUnit::BYTES));
}

DataSize
DataSize::parse(const std::string &text, const DataUnit &defaultUnit)
{
	if (text.empty())
		throw IllegalArgumentException("text must not be empty");

	size_t index = 0;
	long negate = 1;

	if (text[0] == '-')
	{
		negate *= -1;
		index++;
	}

	size_t start = index;
	while (index < text.size() && std::isdigit(text[index]))
		index++;

	std::stringstream stream;
	long value;

	stream << text.substr(start, index - start);
	stream >> value;

	std::string unitText = text.substr(index, text.length() - index);
	const DataUnit &unit = unitText.empty() ? defaultUnit : *DataUnit::fromSuffix(unitText);

	return (of(value, unit));
}
