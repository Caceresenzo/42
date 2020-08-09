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

#include <iostream>
#include <cstdlib>

#include "Bureaucrat.hpp"
#include "Form.hpp"

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

int
main(void)
{
	Bureaucrat bureaucrat("enzo", 3);
	Form form("internship contract", 3, 150);

	bureaucrat.signForm(form);
	bureaucrat.signForm(form);

	bureaucrat.demote(); // Grade = 4
	form = Form(); // Reset 'signed' flag
	bureaucrat.signForm(form);

	bureaucrat.promote(); // Grade = 3
	form = Form(); // Reset 'signed' flag
	bureaucrat.signForm(form);

	bureaucrat.promote(); // Grade = 2
	form = Form(); // Reset 'signed' flag
	bureaucrat.signForm(form);

	std::string msg;

	try
	{
		msg = "normal: 1 - 1";

		Form("xxx", 1, 1);
		xassert(true, msg);
	}
	catch (std::exception &e)
	{
		xassert(false, msg);
	}

	try
	{
		msg = "normal: 1 - 150";

		Form("xxx", 1, 150);
		xassert(true, msg);
	}
	catch (std::exception &e)
	{
		xassert(false, msg);
	}

	try
	{
		msg = "normal: 150 - 1";

		Form("xxx", 150, 1);
		xassert(true, msg);
	}
	catch (std::exception &e)
	{
		xassert(false, msg);
	}

	try
	{
		msg = "normal: 150 - 150";

		Form("xxx", 150, 150);
		xassert(true, msg);
	}
	catch (std::exception &e)
	{
		xassert(false, msg);
	}

	try
	{
		msg = "slightly off: 0 - 1";

		Form("xxx", 0, 1);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to sign is too high", msg);
	}

	try
	{
		msg = "slightly off: 1 - 0";

		Form("xxx", 1, 0);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to execute is too high", msg);
	}

	try
	{
		msg = "completly off: 0 - 0";

		Form("xxx", 0, 0);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to sign is too high", msg);
	}

	try
	{
		msg = "slightly off: 151 - 150";

		Form("xxx", 151, 150);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to sign is too low", msg);
	}

	try
	{
		msg = "slightly off: 150 - 151";

		Form("xxx", 150, 151);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to execute is too low", msg);
	}

	try
	{
		msg = "completly off: 151 - 151";

		Form("xxx", 151, 151);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to sign is too low", msg);
	}

	try
	{
		msg = "negative: -10 - -10";

		Form("xxx", -10, -10);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to sign is too high", msg);
	}

	try
	{
		msg = "big: 500 - 500";

		Form("xxx", 500, 500);
		xassert(false, msg);
	}
	catch (std::exception &e)
	{
		xassert(e.what() == "Req. grade to sign is too low", msg);
	}
}
