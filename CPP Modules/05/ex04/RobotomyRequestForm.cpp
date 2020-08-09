/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:10:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 12:10:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

#include <unistd.h> /* usleep */
#include <iostream>

#ifndef FUNNY
# define FUNNY false
#endif

RobotomyRequestForm::RobotomyRequestForm() :
		Form()
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string target) :
		Form("Robotomy Request", target, 72, 45)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) :
		Form(other)
{
	this->operator =(other);
}

RobotomyRequestForm&
RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	Form::operator =(other);

	return (*this);
}

void
RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);

	if (FUNNY)
	{
		for (int index = 0; index < 4; ++index)
		{
			std::cout << '\a' << "brzz... " << std::flush;
			usleep(200000);
		}
	}
	else
		std::cout << "brzz... brzz... brzz... brzz... ";

	std::cout << std::endl //
	        << getTarget() //
	        << " has been successfully robotimized!" //
	        << std::endl;
}

Form*
RobotomyRequestForm::factory(const std::string target)
{
	return new RobotomyRequestForm(target);
}
