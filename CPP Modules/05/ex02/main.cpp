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
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

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
Bureaucrat theIntern("the intern", 150);

Form*
simple_sign_form_test(Form *form)
{
	std::string msg;

	try
	{
		msg = form->getName() + ": signing unsingned form";

		form->execute(theBoss);

		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(Form::NotSignedException().what() == e.what(), msg);
	}

	form->beSigned(theBoss);

	try
	{
		msg = form->getName() + ": boss signing";

		form->execute(theBoss);

		xassert(true, msg);
	}
	catch (std::exception &e)
	{
		xassert(false, msg);
	}

	try
	{
		msg = form->getName() + ": intern signing";

		form->execute(theIntern);

		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(Form::GradeTooLowException(false).what() == e.what(), msg);
	}

	std::cout << std::endl;

	return (form);
}

Form*
inversed_sign_form_test(Form *form)
{
	form->beSigned(theBoss);

	theBoss.executeForm(*form);
	theIntern.executeForm(*form);

	std::cout << std::endl;

	return (form);
}

int
main(void)
{
	delete (simple_sign_form_test(new ShrubberyCreationForm("xxx")));
	delete (simple_sign_form_test(new RobotomyRequestForm("yyy")));
	delete (simple_sign_form_test(new PresidentialPardonForm("zzz")));

	delete (inversed_sign_form_test(new ShrubberyCreationForm("xxx")));
	delete (inversed_sign_form_test(new RobotomyRequestForm("yyy")));
	delete (inversed_sign_form_test(new PresidentialPardonForm("zzz")));

	system("chmod 000 xxx_shrubbery");
	delete (inversed_sign_form_test(new ShrubberyCreationForm("xxx")));

	system("chmod 777 xxx_shrubbery");
}
