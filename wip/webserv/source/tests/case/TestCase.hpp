/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestCase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 23:41:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/25 23:41:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTCASE_HPP_
# define TESTCASE_HPP_

#include <string>

class TestCase
{
	public:
		typedef int
		(*main_function)(int, char**, char**);

	private:
		std::string m_unit;
		std::string m_name;
		std::string m_location;
		main_function m_function;

	public:
		TestCase();
		TestCase(std::string unit, std::string name, std::string location, main_function function);
		TestCase(const TestCase &other);

		virtual
		~TestCase();

		TestCase&
		operator =(const TestCase &other);

		inline const std::string&
		unit(void) const
		{
			return (m_unit);
		}

		inline const std::string&
		name(void) const
		{
			return (m_name);
		}

		inline const std::string&
		location(void) const
		{
			return (m_location);
		}

		inline main_function
		function(void) const
		{
			return (m_function);
		}
};

#endif /* TESTCASE_HPP_ */
