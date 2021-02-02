/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestCase.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 23:41:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/25 23:41:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/case/TestCase.hpp>
#include <tests/test_unit.hpp>
#include <list>
#include <map>

extern std::map<std::string, std::list<TestCase> > g_test_units_and_cases;

TestCase::TestCase() :
		m_unit(),
		m_name(),
		m_location(),
		m_function(NULL)
{
}

TestCase::TestCase(std::string unit, std::string name, std::string location, main_function function) :
		m_unit(unit),
		m_name(name),
		m_location(location),
		m_function(function)
{
	g_test_units_and_cases[m_unit].push_back(*this);
}

TestCase::TestCase(const TestCase &other) :
		m_name(other.m_name),
		m_location(other.m_location),
		m_function(other.m_function)
{
}

TestCase::~TestCase()
{
}

TestCase&
TestCase::operator =(const TestCase &other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_location = other.m_location;
		m_function = other.m_function;
	}

	return (*this);
}
