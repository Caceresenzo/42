/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/29 10:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "Bureaucrat.hpp"

#include "ShrubberyCreationForm.hpp"

const int Bureaucrat::GRADE_HIGHEST = 1;
const int Bureaucrat::GRADE_LOWEST = 150;

Bureaucrat::Bureaucrat(void) :
		_name("?")
{
	this->_grade = Bureaucrat::GRADE_HIGHEST;
}

Bureaucrat::Bureaucrat(const std::string name, int grade) :
		_name(name)
{
	this->_grade = ensureGradeRange(grade);
}

Bureaucrat::~Bureaucrat(void)
{
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) :
		_name(other._name)
{
	this->operator =(other);
}

Bureaucrat&
Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
	{
		this->_grade = ensureGradeRange(other._grade);
	}

	return (*this);
}

int
Bureaucrat::ensureGradeRange(int grade)
{
	if (grade < Bureaucrat::GRADE_HIGHEST)
		throw Bureaucrat::GradeTooHighException();
	if (grade > Bureaucrat::GRADE_LOWEST)
		throw Bureaucrat::GradeTooLowException();

	return (grade);
}

int
Bureaucrat::promote()
{
	return (this->_grade = ensureGradeRange(_grade - 1));
}

int
Bureaucrat::demote()
{
	return (this->_grade = ensureGradeRange(_grade + 1));
}

void
Bureaucrat::signForm(Form &form)
{
	bool alreadySigned = form.isSigned();
	bool success = false;

	if (!alreadySigned)
	{
		try
		{
			form.beSigned(*this);

			success = true;
		}
		catch (std::exception &exception)
		{
		}
	}

	std::cout << _name;

	if (success)
		std::cout << " signs " << form;
	else
		std::cout << " cant signs " //
		        << form.getName() //
		        << " because " //
		        << (alreadySigned ? "it was already signed" : "his grade is too low");

	std::cout << std::endl;
}

void
Bureaucrat::executeForm(Form const &form)
{
	std::string error;
	bool success = false;

	try
	{
		form.execute(*this);

		success = true;
	}
	catch (ShrubberyCreationForm::IOException &e)
	{
		error = std::string("IO Error: ").append(e.what());
	}
	catch (std::exception &e)
	{
		error = std::string(e.what());
	}

	if (success)
		std::cout << this->_name << " executs " << form << std::endl;
	else
		std::cout << this->_name << " cant executs " << form.getName() << ": " << error << std::endl;
}

const std::string&
Bureaucrat::getName() const
{
	return (this->_name);
}

int
Bureaucrat::getGrade() const
{
	return (this->_grade);
}

Bureaucrat::GradeTooHighException::GradeTooHighException(void) :
		std::exception()
{
}

Bureaucrat::GradeTooHighException::~GradeTooHighException(void) throw ()
{
}

Bureaucrat::GradeTooHighException::GradeTooHighException(
        const GradeTooHighException &other)
{
	this->operator =(other);
}

Bureaucrat::GradeTooHighException&
Bureaucrat::GradeTooHighException::operator=(const GradeTooHighException &other)
{
	(void)other;
	return (*this);
}

const char*
Bureaucrat::GradeTooHighException::what() const throw ()
{
	return "Grade is too high";
}

Bureaucrat::GradeTooLowException::GradeTooLowException(void) :
		std::exception()
{
}

Bureaucrat::GradeTooLowException::~GradeTooLowException(void) throw ()
{
}

Bureaucrat::GradeTooLowException::GradeTooLowException(
        const GradeTooLowException &other)
{
	this->operator =(other);
}

Bureaucrat::GradeTooLowException&
Bureaucrat::GradeTooLowException::operator=(const GradeTooLowException &other)
{
	(void)other;
	return (*this);
}

const char*
Bureaucrat::GradeTooLowException::what() const throw ()
{
	return "Grade is too low";
}

std::ostream&
operator<<(std::ostream &outStream, const Bureaucrat &bureaucrat)
{
	return (outStream << bureaucrat.getName() //
	        << ", bureaucrat grade " //
	        << bureaucrat.getGrade());
}

