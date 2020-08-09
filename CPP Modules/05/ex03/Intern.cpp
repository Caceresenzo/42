/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:48:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 15:48:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

#include <iostream>
#include <string>

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

const std::string Intern::FORM_NAMES[FORM_IMPL_COUNT] =
{
	"shrubbery creation",
	"robotomy request",
	"presidential pardon"
};

Form*
(*Intern::FORM_FACTORIES[FORM_IMPL_COUNT])(const std::string) =
{
	&ShrubberyCreationForm::factory,
	&RobotomyRequestForm::factory,
	&PresidentialPardonForm::factory
};

static bool
insensitiveEquals(unsigned char a, unsigned char b)
{
	return std::tolower(a) == std::tolower(b);
}

static bool
insensitiveEquals(const std::string &a, const std::string &b)
{
	size_t length = a.length();

	if ((length = a.length()) != b.length())
		return (false);

	for (size_t index = 0; index < length; ++index)
	{
		if (!insensitiveEquals(a.at(index), b.at(index)))
			return (false);
	}

	return (true);
}

Intern::Intern()
{
}

Intern::~Intern()
{
}

Intern::Intern(const Intern &other)
{
	this->operator =(other);
}

Intern&
Intern::operator=(const Intern &other)
{
	(void)other;

	return (*this);
}

Form*
Intern::makeForm(const std::string name, const std::string target) const
{
	for (int index = 0; index < FORM_IMPL_COUNT; ++index)
	{
		if (insensitiveEquals(Intern::FORM_NAMES[index], name))
		{
			Form *form = ((*(Intern::FORM_FACTORIES[index]))(target));

			std::cout << "Intern creates " << form->getName() << std::endl;

			return (form);
		}
	}

	throw Intern::FormNotFoundException(name);
}

Intern::FormNotFoundException::FormNotFoundException(void) :
		std::exception(), //
		_message("Form not found")
{
}

Intern::FormNotFoundException::FormNotFoundException(const std::string formName) :
		std::exception(), //
		_message("Form with name '" + formName + "' is not found")
{
}

Intern::FormNotFoundException::FormNotFoundException(
        const FormNotFoundException &other) :
		std::exception(), //
		_message(other._message)
{
	this->operator =(other);
}

Intern::FormNotFoundException::~FormNotFoundException(void) throw ()
{
}

Intern::FormNotFoundException&
Intern::FormNotFoundException::operator =(const FormNotFoundException &other)
{
	(void)other;

	return (*this);
}

const char*
Intern::FormNotFoundException::what() const throw ()
{
	return this->_message.c_str();
}
