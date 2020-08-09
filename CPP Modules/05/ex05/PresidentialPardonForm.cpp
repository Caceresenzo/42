/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:28:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 12:28:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() :
		Form()
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string target) :
		Form("Presidential Pardon", target, 25, 5)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm::PresidentialPardonForm(
        const PresidentialPardonForm &other) :
		Form(other)
{
	this->operator =(other);
}

PresidentialPardonForm&
PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	Form::operator =(other);

	return (*this);
}

void
PresidentialPardonForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);

	std::cout << getTarget() //
	        << " has been forgiven by Zafod Beeblebrox" //
	        << std::endl;
}

Form*
PresidentialPardonForm::factory(const std::string target)
{
	return new PresidentialPardonForm(target);
}
