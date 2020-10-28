/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataUnit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:07:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 15:07:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/IllegalArgumentException.hpp>
#include <util/unit/DataUnit.hpp>
#include <iterator>
#include <string>

#define DEFINE_UNIT(name, suffix, size) ENUM_DEFINE(DataUnit, name, DataUnit(suffix, size));

DEFINE_UNIT(BYTES/*        */,"B", DataSize::ofBytes(1));
DEFINE_UNIT(KILOBYTES/*    */,"KB", DataSize::ofKilobytes(1));
DEFINE_UNIT(MEGABYTES/*    */,"MB", DataSize::ofMegabytes(1));
DEFINE_UNIT(GIGABYTES/*    */,"GB", DataSize::ofGigabytes(1));
DEFINE_UNIT(TERABYTES/*    */,"TB", DataSize::ofTerabytes(1));

DataUnit::DataUnit() :
		m_suffix(),
		m_size()
{
}

DataUnit::DataUnit(const std::string &suffix, const DataSize &size) :
		m_suffix(suffix),
		m_size(size)
{
}

DataUnit::DataUnit(const DataUnit &other) :
		m_suffix(other.m_suffix),
		m_size(other.m_size)
{
}

DataUnit::~DataUnit()
{
}

DataUnit&
DataUnit::operator=(const DataUnit &other)
{
	if (this != &other)
	{
		m_suffix = other.m_suffix;
		m_size = other.m_size;
	}

	return (*this);
}

const std::string&
DataUnit::suffix() const
{
	return (m_suffix);
}

const DataSize&
DataUnit::size() const
{
	return (m_size);
}

DataUnit*
DataUnit::fromSuffix(const std::string &suffix)
{
	iterator it = values().begin();
	iterator ite = values().end();

	while (it != ite)
	{
		if ((*it)->suffix() == suffix)
			return (*it);

		it++;
	}

	throw IllegalArgumentException("unknown data unit prefix: " + suffix);
}
