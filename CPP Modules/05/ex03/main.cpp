/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/29 10:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "Intern.hpp"

#define xassert(exp, msg) \
	{ \
		bool ___ok = (exp); \
		if (___ok) \
			std::cout << "\e[92mPASSED\e[39m: " << msg << std::endl; \
		if (!___ok) { \
			std::cout << "\e[91mFAILED\e[39m: " << msg << "    (line: " << __LINE__ << ")" << std::endl; \
			exit(1); \
		} \
	}

Bureaucrat theBoss("the boss", 1);

Form*
simple_intern_make_test(std::string name, std::string target)
{
	std::string msg;

	Intern intern;
	Form *form;

	try
	{
		msg = "'" + name + "'";

		form = intern.makeForm(name, target);
		form->beSigned(theBoss);
		form->execute(theBoss);

		xassert(true, msg);
	}
	catch (std::exception &e)
	{
		xassert(false, msg);
	}

	std::cout << std::endl;

	return (form);
}

void
inversed_intern_make_test(std::string name, std::string target)
{
	std::string msg;

	Intern intern;
	Form *form;

	try
	{
		msg = "'" + name + "'";

		form = intern.makeForm(name, target);

		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		xassert(std::string(Intern::FormNotFoundException(name).what()) == e.what(), msg);
	}

	std::cout << std::endl;
}

int
main(void)
{
	delete simple_intern_make_test("shrubbery creation", "xxx");
	delete simple_intern_make_test("robotomy request", "yyy");
	delete simple_intern_make_test("presidential pardon", "zzz");

	delete simple_intern_make_test("Shrubbery Creation", "xxx");
	delete simple_intern_make_test("Robotomy Request", "yyy");
	delete simple_intern_make_test("Presidential Pardon", "zzz");

	delete simple_intern_make_test("SHRUBBERY CREATION", "xxx");
	delete simple_intern_make_test("ROBOTOMY REQUEST", "yyy");
	delete simple_intern_make_test("PRESIDENTIAL PARDON", "zzz");

	inversed_intern_make_test("god mode", "me");
}
